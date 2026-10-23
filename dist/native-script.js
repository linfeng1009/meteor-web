// Original Meteor Blade PST interpreter. Source is tokenized and interpreted;
// it is never evaluated as JavaScript. Engine APIs are supplied explicitly.
const TYPES = new Set(['int', 'float', 'string', 'bool', 'void']);
const ASSIGN = new Set(['=', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=']);
const PREC = { ',': 0, '=': 1, '+=': 1, '-=': 1, '*=': 1, '/=': 1, '%=': 1, '&=': 1, '|=': 1, '^=': 1,
  '||': 3, '&&': 4, '|': 5, '^': 6, '&': 7, '==': 8, '!=': 8, '<': 9, '<=': 9, '>': 9, '>=': 9,
  '<<': 10, '>>': 10, '+': 11, '-': 11, '*': 12, '/': 12, '%': 12 };
const box = (value, type = typeof value === 'string' ? 'string' : Number.isInteger(value) ? 'int' : 'float') => ({ value, type });
const truth = value => value !== 0 && value !== '' && value !== false && value != null;

export class NativeScriptError extends Error {
  constructor(message, location, code = 'SCRIPT_ERROR') {
    super(`${location ? `${location.file}:${location.line}:${location.column}: ` : ''}${message}`);
    this.name = 'NativeScriptError'; this.code = code; this.location = location;
  }
}

function tokens(source, file) {
  const result = []; let i = 0, line = 1, column = 1;
  const loc = () => ({ file, line, column });
  const advance = () => { const c = source[i++]; if (c === '\n') { line++; column = 1; } else column++; return c; };
  while (i < source.length) {
    const c = source[i];
    if (/\s|\uFEFF/.test(c)) { advance(); continue; }
    if (source.startsWith('//', i)) { while (i < source.length && source[i] !== '\n') advance(); continue; }
    if (source.startsWith('/*', i)) {
      const start = loc(); advance(); advance();
      while (i < source.length && !source.startsWith('*/', i)) advance();
      if (i === source.length) throw new NativeScriptError('Unterminated comment', start, 'PARSE_ERROR');
      advance(); advance(); continue;
    }
    const location = loc();
    if (c === '#') {
      let value = ''; advance(); while (i < source.length && source[i] !== '\n') value += advance();
      result.push({ kind: 'directive', value: value.trim(), location }); continue;
    }
    if (c === '"') {
      let value = ''; advance(); let closed = false;
      while (i < source.length) {
        const next = advance();
        if (next === '"') { closed = true; break; }
        if (next === '\\') {
          const escaped = advance(), escapes = { n: '\n', r: '\r', t: '\t', '"': '"', '\\': '\\' };
          value += Object.hasOwn(escapes, escaped) ? escapes[escaped] : '\\' + escaped;
        } else value += next;
      }
      if (!closed) throw new NativeScriptError('Unterminated string', location, 'PARSE_ERROR');
      result.push({ kind: 'string', value, location }); continue;
    }
    const number = source.slice(i).match(/^(?:0[xX][\da-fA-F]+|(?:\d+(?:\.\d*)?|\.\d+)(?:[eE][+-]?\d+)?)/);
    if (number) {
      const raw = number[0]; for (let j = 0; j < raw.length; j++) advance();
      result.push({ kind: 'number', value: Number(raw), numberType: /[.eE]/.test(raw) && !/^0x/i.test(raw) ? 'float' : 'int', location }); continue;
    }
    const name = source.slice(i).match(/^[A-Za-z_]\w*/);
    if (name) {
      for (let j = 0; j < name[0].length; j++) advance();
      result.push({ kind: 'name', value: name[0], location }); continue;
    }
    const operator = ['++', '--', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '==', '!=', '<=', '>=', '&&', '||', '<<', '>>'].find(op => source.startsWith(op, i));
    if (operator || '{}()[];,+-*/%=!<>?:&|^~'.includes(c)) {
      const value = operator || c; for (let j = 0; j < value.length; j++) advance();
      result.push({ kind: 'punct', value, location }); continue;
    }
    throw new NativeScriptError(`Unsupported character ${JSON.stringify(c)}`, location, 'PARSE_ERROR');
  }
  result.push({ kind: 'eof', value: '<eof>', location: loc() }); return result;
}

class Parser {
  constructor(source, file) { this.tokens = tokens(source, file); this.index = 0; this.file = file; }
  get current() { return this.tokens[this.index]; }
  at(value) { return this.current.value === value; }
  take() { return this.tokens[this.index++]; }
  eat(value) { if (this.at(value)) { this.take(); return true; } return false; }
  expect(value) { if (!this.at(value)) this.fail(`Expected ${value}, found ${this.current.value}`); return this.take(); }
  name() { if (this.current.kind !== 'name') this.fail('Expected identifier'); return this.take(); }
  fail(message) { throw new NativeScriptError(message, this.current.location, 'PARSE_ERROR'); }
  program() {
    const body = [];
    while (this.current.kind !== 'eof') {
      if (this.eat(';')) continue;
      if (this.current.kind === 'directive') {
        const token = this.take(); let match;
        if ((match = token.value.match(/^include\s+"([^"]+)"\s*$/))) body.push({ type: 'Include', name: match[1], location: token.location });
        else if ((match = token.value.match(/^define\s+(\w+)\s+(.+)$/))) {
          const parser = new Parser(match[2], this.file), value = parser.expression();
          if (parser.current.kind !== 'eof') parser.fail('Unexpected macro suffix');
          body.push({ type: 'Define', name: match[1], value, location: token.location });
        } else this.fail(`Unsupported preprocessor directive #${token.value}`);
        continue;
      }
      const declaredType = TYPES.has(this.current.value) ? this.take().value : null;
      const id = this.name();
      if (this.eat('(')) {
        const parameters = [];
        if (!this.at(')')) do {
          const type = TYPES.has(this.current.value) ? this.take().value : 'int';
          if (type === 'void' && this.at(')')) break;
          const parameter = this.name(); parameters.push({ name: parameter.value, valueType: type, location: parameter.location });
        } while (this.eat(','));
        this.expect(')');
        body.push({ type: 'Function', name: id.value, returnType: declaredType, parameters, body: this.block(), location: id.location });
      } else {
        if (!declaredType || declaredType === 'void') this.fail('A global variable needs a value type');
        body.push(this.declaration(declaredType, id));
      }
    }
    return { type: 'Program', file: this.file, body };
  }
  declaration(valueType = this.take().value, first = this.name(), semicolon = true) {
    const declarations = []; let id = first;
    do {
      const size = this.eat('[') ? (() => { const value = this.expression(); this.expect(']'); return value; })() : null;
      let value = null;
      if (this.eat('=')) {
        if (this.eat('{')) {
          const elements = []; if (!this.at('}')) do { elements.push(this.expression(1)); } while (this.eat(','));
          this.expect('}'); value = { type: 'ArrayLiteral', elements, location: id.location };
        } else value = this.expression(1);
      }
      declarations.push({ name: id.value, size, value, location: id.location });
      if (!this.eat(',')) break; id = this.name();
    } while (true);
    if (semicolon) this.expect(';');
    return { type: 'Declaration', valueType, declarations, location: first.location };
  }
  block() {
    const start = this.expect('{'), body = [];
    while (!this.at('}')) { if (this.current.kind === 'eof') this.fail('Truncated block'); body.push(this.statement()); }
    this.expect('}'); return { type: 'Block', body, location: start.location };
  }
  parenthesized() { this.expect('('); const value = this.expression(); this.expect(')'); return value; }
  statement() {
    const token = this.current;
    if (this.at('{')) return this.block();
    if (this.eat(';')) return { type: 'Empty', location: token.location };
    if (TYPES.has(token.value)) return this.declaration();
    if (this.eat('if')) {
      const condition = this.parenthesized(), consequent = this.statement();
      return { type: 'If', condition, consequent, alternate: this.eat('else') ? this.statement() : null, location: token.location };
    }
    if (this.eat('while')) return { type: 'While', condition: this.parenthesized(), body: this.statement(), location: token.location };
    if (this.eat('for')) {
      this.expect('('); let init = null;
      if (!this.at(';')) init = TYPES.has(this.current.value) ? this.declaration() : (() => { const e = this.expression(); this.expect(';'); return e; })();
      else this.expect(';');
      const condition = this.at(';') ? null : this.expression(); this.expect(';');
      const update = this.at(')') ? null : this.expression(); this.expect(')');
      return { type: 'For', init, condition, update, body: this.statement(), location: token.location };
    }
    if (this.eat('return')) { const value = this.at(';') ? null : this.expression(); this.expect(';'); return { type: 'Return', value, location: token.location }; }
    if (this.eat('break') || this.eat('continue')) { this.expect(';'); return { type: token.value === 'break' ? 'Break' : 'Continue', location: token.location }; }
    const expression = this.expression(); this.expect(';'); return { type: 'ExpressionStatement', expression, location: token.location };
  }
  expression(minimum = 0) {
    let left; const token = this.take();
    if (token.kind === 'number' || token.kind === 'string') left = { type: 'Literal', value: token.value, valueType: token.numberType || 'string', location: token.location };
    else if (token.kind === 'name') left = ['true', 'false'].includes(token.value) ? { type: 'Literal', value: Number(token.value === 'true'), valueType: 'int', location: token.location } : { type: 'Identifier', name: token.value, location: token.location };
    else if (token.value === '(') { left = this.expression(); this.expect(')'); }
    else if (['+', '-', '!', '~', '++', '--'].includes(token.value)) left = { type: 'Unary', operator: token.value, argument: this.expression(13), prefix: true, location: token.location };
    else this.fail(`Expected expression, found ${token.value}`);
    while (true) {
      const next = this.current;
      if (this.eat('(')) {
        if (left.type !== 'Identifier') this.fail('Only named script/native functions can be called');
        const args = []; if (!this.at(')')) do { args.push(this.expression(1)); } while (this.eat(','));
        this.expect(')'); left = { type: 'Call', name: left.name, arguments: args, location: left.location }; continue;
      }
      if (this.eat('[')) { const index = this.expression(); this.expect(']'); left = { type: 'Index', object: left, index, location: left.location }; continue; }
      if (this.eat('++') || this.eat('--')) { left = { type: 'Unary', operator: next.value, argument: left, prefix: false, location: left.location }; continue; }
      if (next.value === '?' && minimum <= 2) {
        this.take(); const consequent = this.expression(); this.expect(':'); const alternate = this.expression(2);
        left = { type: 'Conditional', condition: left, consequent, alternate, location: left.location }; continue;
      }
      const precedence = PREC[next.value]; if (precedence == null || precedence < minimum) break;
      this.take(); const right = this.expression(precedence + (ASSIGN.has(next.value) ? 0 : 1));
      left = { type: ASSIGN.has(next.value) ? 'Assignment' : 'Binary', operator: next.value, left, right, location: left.location };
    }
    return left;
  }
}

export function parsePst(source, { file = '<script.pst>' } = {}) {
  if (typeof source !== 'string') throw new TypeError('parsePst expects decoded text');
  return new Parser(source, file).program();
}

export function normalizePstPath(path, fromFile = null) {
  const clean = value => value.replaceAll('\\', '/');
  const parts = (fromFile ? clean(fromFile).split('/').slice(0, -1) : []).concat(clean(path).split('/'));
  const result = [];
  for (const part of parts) {
    if (!part || part === '.') continue;
    if (part === '..') { if (!result.length) throw new NativeScriptError('Include escapes the supplied source bundle', null, 'MISSING_INCLUDE'); result.pop(); }
    else result.push(part);
  }
  return result.join('/').toLowerCase();
}

export function createPstIncludeResolver(sources) {
  const entries = sources instanceof Map ? sources : new Map(Object.entries(sources));
  const indexed = new Map([...entries].map(([file, source]) => [normalizePstPath(file), source]));
  return (name, fromFile) => {
    const file = normalizePstPath(name, fromFile), source = indexed.get(file);
    if (typeof source !== 'string') throw new NativeScriptError(`Include ${file} is absent from the supplied source bundle`, null, 'MISSING_INCLUDE');
    return { file, source };
  };
}

class Environment {
  constructor(parent = null) { this.parent = parent; this.bindings = new Map(); }
  find(name) { return this.bindings.has(name) ? this.bindings.get(name) : this.parent?.find(name); }
}

export class NativeScriptVM {
  constructor({ natives = {}, maxSteps = 200000, maxCallDepth = 64, onEvent = () => {}, onUnknownNative = null } = {}) {
    this.natives = natives instanceof Map ? new Map(natives) : new Map(Object.entries(natives));
    this.maxSteps = maxSteps; this.maxCallDepth = maxCallDepth; this.onEvent = onEvent; this.onUnknownNative = onUnknownNative;
    this.global = new Environment(); this.functions = new Map(); this.programs = []; this.loadedFiles = new Set(); this.callDepth = 0; this.remaining = maxSteps;
  }
  error(message, node, code) { const error = new NativeScriptError(message, node?.location, code); this.onEvent({ type: 'script-error', error }); throw error; }
  step(node) { if (--this.remaining < 0) this.error('Execution step budget exceeded', node, 'STEP_LIMIT'); }
  coerce(value, type, node) {
    if (type === 'string') return String(value ?? '');
    if (type === 'bool') return Number(truth(value));
    if (typeof value !== 'number' || !Number.isFinite(value)) this.error(`Expected finite ${type}, received ${String(value)}`, node, 'TYPE_ERROR');
    return type === 'int' ? Math.trunc(value) : value;
  }
  declare(node, env) {
    for (const declaration of node.declarations) {
      if (env.bindings.has(declaration.name)) this.error(`Duplicate variable ${declaration.name}`, declaration, 'DUPLICATE_NAME');
      let value;
      if (declaration.size) {
        const count = this.evaluate(declaration.size, env).value;
        if (!Number.isInteger(count) || count < 0 || count > 1000000) this.error('Invalid array length', declaration, 'ARRAY_BOUNDS');
        value = Array(count).fill(node.valueType === 'string' ? '' : 0);
        if (declaration.value) {
          if (declaration.value.type !== 'ArrayLiteral' || declaration.value.elements.length > count) this.error('Invalid array initializer', declaration, 'TYPE_ERROR');
          declaration.value.elements.forEach((element, i) => { value[i] = this.coerce(this.evaluate(element, env).value, node.valueType, element); });
        }
      } else value = declaration.value ? this.coerce(this.evaluate(declaration.value, env).value, node.valueType, declaration) : node.valueType === 'string' ? '' : 0;
      env.bindings.set(declaration.name, { value, type: node.valueType, array: !!declaration.size, constant: false });
    }
  }
  load(source, { file = '<script.pst>', resolveInclude = null } = {}) {
    this.remaining = this.maxSteps;
    const declarations = [], collect = (input, filename, ancestry = []) => {
      if (ancestry.includes(filename)) this.error(`Include cycle: ${[...ancestry, filename].join(' -> ')}`, null, 'INCLUDE_CYCLE');
      if (this.loadedFiles.has(filename)) return;
      const program = typeof input === 'string' ? parsePst(input, { file: filename }) : input;
      this.loadedFiles.add(filename); this.programs.push(program);
      for (const node of program.body) {
        if (node.type === 'Include') {
          if (!resolveInclude) this.error(`No resolver for include ${node.name}`, node, 'MISSING_INCLUDE');
          const resolved = resolveInclude(node.name, filename);
          if (resolved == null || typeof resolved?.then === 'function') this.error(`Include resolver must return decoded text synchronously: ${node.name}`, node, 'MISSING_INCLUDE');
          collect(typeof resolved === 'string' ? resolved : resolved.source, typeof resolved === 'string' ? `${filename}:${node.name}` : resolved.file || node.name, [...ancestry, filename]);
        } else if (node.type === 'Function') {
          if (this.functions.has(node.name)) this.error(`Duplicate function ${node.name}`, node, 'DUPLICATE_NAME');
          this.functions.set(node.name, node);
        } else declarations.push(node);
      }
    };
    collect(source, file);
    for (const node of declarations) {
      if (node.type === 'Define') {
        if (this.global.bindings.has(node.name)) this.error(`Duplicate constant ${node.name}`, node, 'DUPLICATE_NAME');
        const value = this.evaluate(node.value, this.global); this.global.bindings.set(node.name, { ...value, constant: true, array: false });
      } else this.declare(node, this.global);
    }
    return this;
  }
  hasFunction(name) { return this.functions.has(name); }
  getGlobal(name) { const binding = this.global.find(name); if (!binding) throw new NativeScriptError(`Unknown global ${name}`, null, 'UNKNOWN_NAME'); return Array.isArray(binding.value) ? binding.value.slice() : binding.value; }
  setGlobal(name, value) { const ref = this.reference({ type: 'Identifier', name }, this.global); ref.set(value); }
  snapshot() { return Object.fromEntries([...this.global.bindings].map(([name]) => [name, this.getGlobal(name)])); }
  getNativeRequirements() {
    const calls = new Map();
    const visit = node => {
      if (!node || typeof node !== 'object') return;
      if (Array.isArray(node)) { node.forEach(visit); return; }
      if (node.type === 'Call' && !this.functions.has(node.name)) {
        if (!calls.has(node.name)) calls.set(node.name, []); calls.get(node.name).push(node.location);
      }
      for (const [key, value] of Object.entries(node)) if (key !== 'location') visit(value);
    };
    this.programs.forEach(visit); return [...calls].sort(([a], [b]) => a.localeCompare(b)).map(([name, locations]) => ({ name, supplied: this.natives.has(name), locations }));
  }
  reference(node, env) {
    if (node.type === 'Identifier') {
      const binding = env.find(node.name); if (!binding) this.error(`Unknown variable ${node.name}`, node, 'UNKNOWN_NAME');
      return { name: node.name, get: () => box(binding.value, binding.type), set: value => {
        if (binding.constant) this.error(`Cannot assign constant ${node.name}`, node, 'TYPE_ERROR');
        if (binding.array) this.error('Cannot assign an entire array', node, 'TYPE_ERROR');
        binding.value = this.coerce(value, binding.type, node); return box(binding.value, binding.type);
      } };
    }
    if (node.type === 'Index') {
      const object = this.evaluate(node.object, env), index = this.evaluate(node.index, env).value;
      if (!Array.isArray(object.value) || !Number.isInteger(index) || index < 0 || index >= object.value.length) this.error(`Array index ${index} is out of bounds`, node, 'ARRAY_BOUNDS');
      return { name: `${node.object.name || 'array'}[${index}]`, get: () => box(object.value[index], object.type),
        set: value => { object.value[index] = this.coerce(value, object.type, node); return box(object.value[index], object.type); } };
    }
    this.error('A writable variable or array element is required', node, 'TYPE_ERROR');
  }
  binary(operator, left, right, node) {
    const a = left.value, b = right.value, numericType = left.type === 'int' && right.type === 'int' ? 'int' : 'float';
    if (operator === ',') return right;
    if (['==', '!=', '<', '<=', '>', '>='].includes(operator)) {
      return box(Number(({ '==': () => a === b, '!=': () => a !== b, '<': () => a < b, '<=': () => a <= b, '>': () => a > b, '>=': () => a >= b })[operator]() ), 'int');
    }
    if (operator === '+' && (left.type === 'string' || right.type === 'string')) return box(String(a) + String(b), 'string');
    if (typeof a !== 'number' || typeof b !== 'number') this.error(`Numeric operands required for ${operator}`, node, 'TYPE_ERROR');
    if ((operator === '/' || operator === '%') && b === 0) this.error('Division by zero', node, 'DIVISION_BY_ZERO');
    const operations = { '+': () => a + b, '-': () => a - b, '*': () => a * b,
      '/': () => numericType === 'int' ? Math.trunc(a / b) : a / b, '%': () => a % b,
      '&': () => a & b, '|': () => a | b, '^': () => a ^ b, '<<': () => a << b, '>>': () => a >> b };
    if (!operations[operator]) this.error(`Unsupported operator ${operator}`, node, 'TYPE_ERROR');
    return box(operations[operator](), ['&', '|', '^', '<<', '>>'].includes(operator) ? 'int' : numericType);
  }
  evaluate(node, env) {
    this.step(node);
    switch (node.type) {
      case 'Literal': return box(node.value, node.valueType);
      case 'Identifier': case 'Index': return this.reference(node, env).get();
      case 'Conditional': return this.evaluate(truth(this.evaluate(node.condition, env).value) ? node.consequent : node.alternate, env);
      case 'Assignment': {
        const ref = this.reference(node.left, env), value = this.evaluate(node.right, env);
        return ref.set(node.operator === '=' ? value.value : this.binary(node.operator.slice(0, -1), ref.get(), value, node).value);
      }
      case 'Unary': {
        if (node.operator === '++' || node.operator === '--') {
          const ref = this.reference(node.argument, env), old = ref.get(), updated = ref.set(old.value + (node.operator === '++' ? 1 : -1));
          return node.prefix ? updated : old;
        }
        const arg = this.evaluate(node.argument, env);
        if (node.operator === '!') return box(Number(!truth(arg.value)), 'int');
        if (typeof arg.value !== 'number') this.error('Numeric unary operand required', node, 'TYPE_ERROR');
        return box(node.operator === '-' ? -arg.value : node.operator === '~' ? ~arg.value : arg.value, arg.type);
      }
      case 'Binary': {
        const left = this.evaluate(node.left, env);
        if (node.operator === '&&') return box(Number(truth(left.value) && truth(this.evaluate(node.right, env).value)), 'int');
        if (node.operator === '||') return box(Number(truth(left.value) || truth(this.evaluate(node.right, env).value)), 'int');
        return this.binary(node.operator, left, this.evaluate(node.right, env), node);
      }
      case 'Call': {
        const refs = [], args = node.arguments.map((argument, i) => {
          const writable = argument.type === 'Identifier' || argument.type === 'Index';
          refs[i] = writable ? this.reference(argument, env) : null;
          return refs[i] ? refs[i].get() : this.evaluate(argument, env);
        });
        if (this.functions.has(node.name)) return this.invoke(node.name, args, node);
        const native = this.natives.get(node.name), values = args.map(a => a.value);
        if (typeof native !== 'function') {
          const event = { type: 'unknown-native', name: node.name, arguments: values, location: node.location };
          this.onEvent(event); this.onUnknownNative?.(event);
          this.error(`Native API ${node.name} is not supplied`, node, 'UNKNOWN_NATIVE');
        }
        const context = { vm: this, name: node.name, location: node.location,
          getArg: index => refs[index] ? refs[index].get().value : values[index],
          setArg: (index, value) => { if (!refs[index]) this.error(`Argument ${index} of ${node.name} is not writable`, node, 'TYPE_ERROR'); return refs[index].set(value).value; },
          arguments: values.slice(), references: refs.map(ref => ref?.name || null) };
        let result;
        try { result = native.apply(context, values); }
        catch (error) { if (error instanceof NativeScriptError) throw error; this.error(`Native API ${node.name}: ${error.message}`, node, 'NATIVE_ERROR'); }
        if (result && typeof result.then === 'function') this.error(`Native API ${node.name} returned a Promise; PST APIs must be synchronous`, node, 'ASYNC_NATIVE');
        this.onEvent({ type: 'native-call', name: node.name, arguments: values, result, location: node.location });
        return box(result, result == null ? 'void' : undefined);
      }
      default: this.error(`Unsupported expression ${node.type}`, node, 'TYPE_ERROR');
    }
  }
  execute(node, env) {
    this.step(node);
    switch (node.type) {
      case 'Empty': return null;
      case 'Declaration': this.declare(node, env); return null;
      case 'ExpressionStatement': this.evaluate(node.expression, env); return null;
      case 'Block': {
        const scope = new Environment(env);
        for (const statement of node.body) { const control = this.execute(statement, scope); if (control) return control; }
        return null;
      }
      case 'If': return truth(this.evaluate(node.condition, env).value) ? this.execute(node.consequent, env) : node.alternate ? this.execute(node.alternate, env) : null;
      case 'While':
        while (truth(this.evaluate(node.condition, env).value)) {
          const control = this.execute(node.body, env); if (control?.type === 'return') return control; if (control?.type === 'break') break;
        }
        return null;
      case 'For': {
        const scope = new Environment(env);
        if (node.init) node.init.type === 'Declaration' ? this.declare(node.init, scope) : this.evaluate(node.init, scope);
        while (!node.condition || truth(this.evaluate(node.condition, scope).value)) {
          this.step(node); const control = this.execute(node.body, scope);
          if (control?.type === 'return') return control; if (control?.type === 'break') break;
          if (node.update) this.evaluate(node.update, scope);
        }
        return null;
      }
      case 'Return': return { type: 'return', value: node.value ? this.evaluate(node.value, env) : box(undefined, 'void') };
      case 'Break': return { type: 'break' };
      case 'Continue': return { type: 'continue' };
      default: this.error(`Unsupported statement ${node.type}`, node, 'TYPE_ERROR');
    }
  }
  invoke(name, args, caller = null) {
    const fn = this.functions.get(name); if (!fn) this.error(`Script function ${name} is absent`, caller, 'UNKNOWN_FUNCTION');
    if (args.length !== fn.parameters.length) this.error(`${name} expects ${fn.parameters.length} arguments, received ${args.length}`, caller || fn, 'ARITY_ERROR');
    if (++this.callDepth > this.maxCallDepth) { this.callDepth--; this.error('Call depth limit exceeded', caller || fn, 'CALL_LIMIT'); }
    const scope = new Environment(this.global);
    try {
      fn.parameters.forEach((parameter, i) => scope.bindings.set(parameter.name, { type: parameter.valueType,
        value: this.coerce(args[i].value, parameter.valueType, parameter), constant: false, array: false }));
      const control = this.execute(fn.body, scope);
      if (control && control.type !== 'return') this.error(`${control.type} outside a loop`, fn, 'CONTROL_FLOW');
      const result = control?.value || box(undefined, 'void');
      return fn.returnType && fn.returnType !== 'void' ? box(this.coerce(result.value, fn.returnType, fn), fn.returnType) : result;
    } finally { this.callDepth--; }
  }
  call(name, args = []) {
    if (this.callDepth === 0) this.remaining = this.maxSteps;
    return this.invoke(name, args.map(value => box(value))).value;
  }
}
