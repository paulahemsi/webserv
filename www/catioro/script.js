
const RACAS_URL = 'https://dog.ceo/api/breeds/list/all';
const seletor = document.querySelector('.racas');

const pata = document.querySelector('.giro');
const img = document.querySelector('.img-catioros');

function buscarRacas() {

    fetch(RACAS_URL)
        .then(function (resposta) {
            return resposta.json();
        })
        .then(function (dados) {
            const objetoRacas = dados.message;
            const arrayRacas = Object.keys(objetoRacas);

            for (let i = 0; i < arrayRacas.length; i++) {
                const opcao = document.createElement('option');
                opcao.innerText = arrayRacas[i];
                opcao.value = arrayRacas[i];
                seletor.appendChild(opcao);
            }
        })

};


buscarRacas();

seletor.addEventListener('change', function (evento) {

    const url = `https://dog.ceo/api/breed/${evento.target.value}/images/random`;
    buscarImagem(url);
});

function buscarImagem(url) {
    pata.classList.add('mostrar');
    img.classList.remove('mostrar');
    fetch(url)
        .then(function(resposta){
            return resposta.json();
        })
        .then(function(dados){
            img.src = dados.message;

        })
};

img.addEventListener("load", function() {
    pata.classList.remove('mostrar');
    img.classList.add('mostrar');
});

