class Carousel{
    constructor(ct,imgs){
        this.ct=ct;

        this.ct.style.position="relative";
        // this.ct.style.border="solid 1px red";
        this.ct.style.backgroundColor="black";
        this.ct.style.overflow="hidden";

        this.wrapper=document.createElement("div");
        this.imgs=imgs;
        this.wrapper.style.width=`${this.ct.clientWidth*this.imgs.length}px`;
        this.wrapper.style.transition="transform 2s";

        this.indicator=document.createElement("div");
        this.indicator.style.display="flex";
        this.indicator.style.position="absolute";
        this.indicator.style.bottom="10px";
        this.indicator.style.width="fit-content";
        this.indicator.style.margin="auto";
        this.indicator.style.left=0;
        this.indicator.style.right=0;

        this.loadImgs(imgs);

        this.current=0;
        this.last=0;
        this.showIndicator();

        const prevBtn=this.initBtn("prev");
        const nextBtn=this.initBtn("next");
        this.ct.appendChild(prevBtn);
        this.ct.appendChild(nextBtn);

        prevBtn.addEventListener("click",(e)=>{
            this.next();
        });
        nextBtn.addEventListener("click",(e)=>{
            this.prev();
        });
    }

    loadImgs(imgs){
        for (const img of imgs){
            const div=document.createElement('div');
            div.style.display="inline-block";
            div.style.width=this.ct.clientWidth+'px';
            div.style.height=this.ct.clientHeight+'px';
            div.style.background='url('+img+') no-repeat center';
            div.style.backgroundSize='contain';

            this.wrapper.appendChild(div);

            const idx=document.createElement("div");
            idx.style.border="solid 1px white";
            idx.style.width=idx.style.height="10px";
            idx.style.borderRadius="5px";
            idx.style.margin="0 3px";
            this.indicator.appendChild(idx);
        }
        this.ct.appendChild(this.wrapper);
        this.ct.appendChild(this.indicator);
    }

    showIndicator(){
        this.indicator.children[this.last].style.backgroundColor="transparent";
        this.indicator.children[this.current].style.backgroundColor="yellow";
    }

    initBtn(direction){
        let btn=document.createElement("div");
        btn.style.position="absolute";
        btn.style.top="0";
        btn.style.lineHeight=this.ct.style.height;
        btn.style.fontSize='48px';
        btn.style.padding="0 10px";
        btn.style.cursor="pointer";

        if (direction==="prev"){
            btn.innerHTML="&#8249;";
            btn.style.left=0;
        } else{
            btn.innerHTML="&#8250;";
            btn.style.right=0;
        }
        btn.style.backgroundColor="transparent";
        btn.style.color="gray";

        btn.addEventListener("mouseover",(e)=>{
            e.target.style.backgroundColor="rgba(100,100,100,0.5)";
            e.target.style.color="white";
        });
        btn.addEventListener("mouseout",(e)=>{
            e.target.style.backgroundColor="transparent";
            e.target.style.color="gray";
        });
        return btn;
    }

    prev(){
        if (this.current>0){
            this.last=this.current;
            this.current--;
        }
        let translateX=this.current*this.ct.clientWidth;
        this.wrapper.style.transform=`translateX(-${translateX}px)`;
        this.showIndicator();
    }

    next(){
        if (this.current<this.imgs.length-1){
            this.last=this.current;
            this.current++;
        }
        let translateX=this.current*this.ct.clientWidth;
        this.wrapper.style.transform=`translateX(-${translateX}px)`;
        this.showIndicator();
    }
}