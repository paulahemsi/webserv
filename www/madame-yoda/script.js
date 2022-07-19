let numero = sortearNumero();
let botao = document.querySelector('.palpite-botao');
let resposta = document.querySelector('.resposta');
let fimDeJogo = false;

function sortearNumero() {
    let numero = Math.floor(Math.random() * 100);
    return numero;
}

function umaChanceAMenos() {
    let planetas = document.querySelectorAll('.icone-tentativa');
    for (let i = 0; i < planetas.length; i++) {
        if (!planetas[i].classList.contains('icone-errou')) {
            planetas[i].src = '/madame-yoda/imagens/planeta-vermelho-borda.svg'
            planetas[i].classList.add('icone-errou');
            
            if (planetas[planetas.length - 1].classList.contains('icone-errou')) {
                botao.textContent = 'Jogar novamente!';
                resposta.textContent = 'Xi. Sem chance ficou você. Adivinhar é uma arte inexata, recomeçar você deve.'
                fimDeJogo = true;
            }
            return;
        }
    };
}

function verficarPalpite() {
    if (!fimDeJogo) {
        let palpite = document.querySelector('.palpite-input').value;
        if (palpite == numero) {
            botao.textContent = 'Jogar novamente!';
            resposta.textContent = 'Sensacional!!!! Adivinhe és você!'
            fimDeJogo = true;
        } else if (palpite < numero) {
            resposta.textContent = 'ih, menor que o número escolhido seu palpite foi... de novo tentar deve!';
            umaChanceAMenos();
        } else if (palpite > numero) {
            resposta.textContent = 'uuuh! Maior que o número escolhido foi sua tentativa! Outro palpite arriscar deve!';
            umaChanceAMenos();
        } else {
            resposta.textContent = 'hm, melhor você escolher um número entre 0 e 100';
        }
    } else {
        recomecar();
    }
}

function recomecar() {
    let planetas = document.querySelectorAll('.icone-tentativa');
    for (let i = 0; i < planetas.length; i++) {
        planetas[i].src = '/madame-yoda/imagens/planeta-azul-borda.svg'
        planetas[i].classList.remove('icone-errou');
    };
    numero = sortearNumero();
    fimDeJogo = false;
    botao.textContent = 'Arriscar!';
    resposta.textContent = 'o.O';
}


botao.addEventListener('click', verficarPalpite);
