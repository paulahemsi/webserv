const tabuleiro = document.querySelector(".tabuleiro");
const cartas = document.querySelectorAll(".cartas");
const arraySrc = [
  './imagens/costas.jpg',
  './imagens/1.jpg',
  './imagens/2.jpg',
  './imagens/3.jpg',
  './imagens/4.jpg',
  './imagens/5.jpg',
  './imagens/6.jpg',
  './imagens/7.jpg',
  './imagens/8.jpg',
  './imagens/9.jpg',
  './imagens/10.jpg',
];
const cartaCostas = './imagens/costas.jpg';
const cartaVazia = './imagens/vazio.jpg';
let contador = 0;
let cartasEscolhidas = [];
let indexCartaEscolhida = [];
const arrayCartas = [
  {
    id: '1',
    img: './imagens/1.jpg'
  },
  {
    id: '2',
    img: './imagens/2.jpg'
  },
  {
    id: '3',
    img: './imagens/3.jpg'
  },
  {
    id: '4',
    img: './imagens/4.jpg'
  },
  {
    id: '5',
    img: './imagens/5.jpg'
  },
  {
    id: '6',
    img: './imagens/6.jpg'
  },
  {
    id: '7',
    img: './imagens/7.jpg'
  },
  {
    id: '8',
    img: './imagens/8.jpg'
  },
  {
    id: '9',
    img: './imagens/9.jpg'
  },
  {
    id: '10',
    img: './imagens/10.jpg'
  },
  {
    id: '1',
    img: './imagens/1.jpg'
  },
  {
    id: '2',
    img: './imagens/2.jpg'
  },
  {
    id: '3',
    img: './imagens/3.jpg'
  },
  {
    id: '4',
    img: './imagens/4.jpg'
  },
  {
    id: '5',
    img: './imagens/5.jpg'
  },
  {
    id: '6',
    img: './imagens/6.jpg'
  },
  {
    id: '7',
    img: './imagens/7.jpg'
  },
  {
    id: '8',
    img: './imagens/8.jpg'
  },
  {
    id: '9',
    img: './imagens/9.jpg'
  },
  {
    id: '10',
    img: './imagens/10.jpg'
  },

]


function novoJogo() {
  for (let i = 0; i < cartas.length; i++) {
    cartas[i].classList.toggle('ativa');
  }
  cartasEscolhidas = [];
  indexCartaEscolhida = [];
  contador = 0;
  embaralharCartas(arrayCartas);
  embaralharTabuleiro();
}

function embaralharCartas(cartas) {
  let indexAtual = cartas.length, valorTemporario, indexRandom;
  while (0 !== indexAtual) {

    indexRandom = Math.floor(Math.random() * indexAtual);
    indexAtual -= 1;

    valorTemporario = cartas[indexAtual];
    cartas[indexAtual] = cartas[indexRandom];
    cartas[indexRandom] = valorTemporario;
  }

  return cartas;
}

function embaralharTabuleiro() {
  const intervalo = setInterval(function () {
    for (let i = 0; i < cartas.length; i++) {
      let carta = cartas[i];
      let index = Math.floor(Math.random() * 10 + 1);
      carta.setAttribute('src', arraySrc[index]);
    }
  }, 30);
  setTimeout(function () {
    clearInterval(intervalo);
    posicionarCartas();
  }, 1750);
};

function posicionarCartas() {
  for (let i = 0; i < cartas.length; i++) {
    let carta = cartas[i];
    carta.setAttribute('src', arraySrc[0]);
    carta.setAttribute('data-index', i);
    carta.addEventListener('click', virarCarta);
  };
}


function virarCarta() {
  if ((cartasEscolhidas.length < 2) && (this.classList.contains('ativa'))) {
    let indexCarta = this.getAttribute('data-index');
    indexCartaEscolhida.push(indexCarta);
    cartasEscolhidas.push(arrayCartas[indexCarta].id);
    this.setAttribute('src', arrayCartas[indexCarta].img);
    if (cartasEscolhidas.length === 2) {
      
      if (indexCartaEscolhida[0] === indexCartaEscolhida[1]) {
        indexCartaEscolhida.pop();
        cartasEscolhidas.pop();
        return;
      } 

      setTimeout(conferirPar, 500)
    }
  }
}

function conferirPar() {
  if (cartasEscolhidas[0] === cartasEscolhidas[1]) {
    for (let i = 0; i < cartasEscolhidas.length; i++) {
      cartas[indexCartaEscolhida[i]].setAttribute('src', cartaVazia);
      cartas[indexCartaEscolhida[i]].classList.toggle('ativa');
    }
    contador++;
    if (contador === 10) {
      setTimeout(novoJogo, 500);
    }
  } else {
    cartas[indexCartaEscolhida[0]].setAttribute('src', cartaCostas);
    cartas[indexCartaEscolhida[1]].setAttribute('src', cartaCostas);
  }
  cartasEscolhidas = [];
  indexCartaEscolhida = [];
}


document.addEventListener('DOMContentLoaded', novoJogo);
