class ImageZoomer {
    constructor(ct) {
        this.scale = 1;
        this.translation = { x: 0, y: 0 };

        if (!ct.clientHeight) {
            ct.style.height = '300px';
        }
        ct.style.overflow = "hidden";
        ct.style.backgroundColor = "gray";

        this.img = new Image();
        this.img.style.top = 0;
        this.img.src = ct.dataset.url;
        ct.appendChild(this.img);

        this.img.onload = () => {
            const s1 = this.img.width / ct.clientWidth;
            const s2 = this.img.height / ct.clientHeight;
            const s = s1 < s2 ? s2 : s1;
            this.img.width = this.img.width / s;
        }

        this.img.addEventListener('mousedown', (e) => {
            e.preventDefault();

            this.startPoint = {
                x: e.offsetX,
                y: e.offsetY
            };
        });

        this.img.addEventListener('mousemove', (e) => {
            if (this.startPoint === undefined) {
                return;
            }

            this.translation.x += (e.offsetX - this.startPoint.x) * this.scale;
            this.translation.y += (e.offsetY - this.startPoint.y) * this.scale;
            this.update();
        });

        this.img.addEventListener('mouseup', (e) => {
            this.startPoint = undefined;
        });
    }

    zoomIn() {
        this.scale += 0.1;
        this.update();
    }

    zoomOut() {
        this.scale -= 0.1;
        this.update();
    }

    zoomRe() {
        this.scale = 1;
        this.update();
    }

    update() {
        this.img.style.transform =
            `translate(${this.translation.x}px,${this.translation.y}px)
        scale(${this.scale})`;
    }
}