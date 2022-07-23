class HtmlPlayer {
    static init() {
        const self = this;
        const xhr = new XMLHttpRequest();

        xhr.onload = () => {
            try {
                const list = JSON.parse(xhr.responseText);
                self.createMenu(list);
            } catch (err) {
                console.error(err);
                alert('读取json文件出错！');
            }
        }

        xhr.open('GET', '../json/playlist.json', true);
        xhr.send(null);
    }

    static createMenu(list) {
        list.forEach(i => {
            let li = document.createElement('li');
            li.innerText = i.name;
            li.dataset.file = i.path;
            this.menu.appendChild(li);

            this.menu.addEventListener('click', e => {
                let filePath = e.target.dataset.file;
                this.player.src = filePath;
                this.player.play();
            });
        });
    }
}

HtmlPlayer.player = document.querySelector('video');
HtmlPlayer.menu = document.querySelector('.menu ol');

HtmlPlayer.init();