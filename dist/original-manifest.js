const url = new URL('./assets/original/manifest.json', import.meta.url);
let pending;

export function loadOriginalManifest() {
  return pending ||= fetch(url).then(response => {
    if (!response.ok) throw new Error('原版资源清单读取失败');
    return response.json();
  }).catch(error => {
    pending = null;
    throw error;
  });
}
