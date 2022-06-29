const board = document.querySelector(".board");
const carts = document.querySelectorAll(".carts");
const arraySrc = [
  '/supreme/img/costas.jpg',
  '/supreme/img/1.jpg',
  '/supreme/img/2.jpg',
  '/supreme/img/3.jpg',
  '/supreme/img/4.jpg',
  '/supreme/img/5.jpg',
  '/supreme/img/6.jpg',
  '/supreme/img/7.jpg',
  '/supreme/img/8.jpg',
  '/supreme/img/9.jpg',
  '/supreme/img/10.jpg',
];
const backImg = '/supreme/img/costas.jpg';
const emptyImg = '/supreme/img/vazio.jpg';
let counter = 0;
let choosenCarts = [];
let index = [];
const arraycarts = [
  {
    id: '1',
    img: '/supreme/img/1.jpg'
  },
  {
    id: '2',
    img: '/supreme/img/2.jpg'
  },
  {
    id: '3',
    img: '/supreme/img/3.jpg'
  },
  {
    id: '4',
    img: '/supreme/img/4.jpg'
  },
  {
    id: '5',
    img: '/supreme/img/5.jpg'
  },
  {
    id: '6',
    img: '/supreme/img/6.jpg'
  },
  {
    id: '7',
    img: '/supreme/img/7.jpg'
  },
  {
    id: '8',
    img: '/supreme/img/8.jpg'
  },
  {
    id: '9',
    img: '/supreme/img/9.jpg'
  },
  {
    id: '10',
    img: '/supreme/img/10.jpg'
  },
  {
    id: '1',
    img: '/supreme/img/1.jpg'
  },
  {
    id: '2',
    img: '/supreme/img/2.jpg'
  },
  {
    id: '3',
    img: '/supreme/img/3.jpg'
  },
  {
    id: '4',
    img: '/supreme/img/4.jpg'
  },
  {
    id: '5',
    img: '/supreme/img/5.jpg'
  },
  {
    id: '6',
    img: '/supreme/img/6.jpg'
  },
  {
    id: '7',
    img: '/supreme/img/7.jpg'
  },
  {
    id: '8',
    img: '/supreme/img/8.jpg'
  },
  {
    id: '9',
    img: '/supreme/img/9.jpg'
  },
  {
    id: '10',
    img: '/supreme/img/10.jpg'
  },

]


function newGame() {
  for (let i = 0; i < carts.length; i++) {
    carts[i].classList.toggle('ativa');
  }
  choosenCarts = [];
  index = [];
  counter = 0;
  shuffle(arraycarts);
  shuffleBoard();
}

function shuffle(carts) {
  let indexAtual = carts.length, valorTemporario, indexRandom;
  while (0 !== indexAtual) {

    indexRandom = Math.floor(Math.random() * indexAtual);
    indexAtual -= 1;

    valorTemporario = carts[indexAtual];
    carts[indexAtual] = carts[indexRandom];
    carts[indexRandom] = valorTemporario;
  }

  return carts;
}

function shuffleBoard() {
  const intervalo = setInterval(function () {
    for (let i = 0; i < carts.length; i++) {
      let carta = carts[i];
      let index = Math.floor(Math.random() * 10 + 1);
      carta.setAttribute('src', arraySrc[index]);
    }
  }, 30);
  setTimeout(function () {
    clearInterval(intervalo);
    posicionarcarts();
  }, 1750);
};

function posicionarcarts() {
  for (let i = 0; i < carts.length; i++) {
    let carta = carts[i];
    carta.setAttribute('src', arraySrc[0]);
    carta.setAttribute('data-index', i);
    carta.addEventListener('click', turn);
  };
}


function turn() {
  if ((choosenCarts.length < 2) && (this.classList.contains('ativa'))) {
    let indexCarta = this.getAttribute('data-index');
    index.push(indexCarta);
    choosenCarts.push(arraycarts[indexCarta].id);
    this.setAttribute('src', arraycarts[indexCarta].img);
    if (choosenCarts.length === 2) {
      
      if (index[0] === index[1]) {
        index.pop();
        choosenCarts.pop();
        return;
      } 

      setTimeout(checkPair, 500)
    }
  }
}

function checkPair() {
  if (choosenCarts[0] === choosenCarts[1]) {
    for (let i = 0; i < choosenCarts.length; i++) {
      carts[index[i]].setAttribute('src', emptyImg);
      carts[index[i]].classList.toggle('ativa');
    }
    counter++;
    if (counter === 10) {
      setTimeout(newGame, 500);
    }
  } else {
    carts[index[0]].setAttribute('src', backImg);
    carts[index[1]].setAttribute('src', backImg);
  }
  choosenCarts = [];
  index = [];
}


document.addEventListener('DOMContentLoaded', newGame);
