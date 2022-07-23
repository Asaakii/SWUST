const $mobile=document.querySelector('input[name="mobile"]');
const $verifyRow=document.querySelector('#verify-row');
const $verifyBtn=$verifyRow.querySelector('button');

$mobile.addEventListener('focus',e=>{
    $verifyRow.style.display='flex';
    $verifyBtn.disabled=true;
});

$mobile.addEventListener('input',e=>{
    const v=$mobile.checkValidiy();
    if(v){
        $verifyBtn.disabled=false;
    }
})