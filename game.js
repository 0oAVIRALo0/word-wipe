const rows = 10;
const columns = 10;

let currentWords = new Set();
let grid = Array.from({ length: rows }, () => Array(columns).fill("-"));

const dr = [0, -1, 0, 1, -1, -1, 1, 1];
const dc = [-1, 0, 1, 0, -1, 1, -1, 1];

function generateRandomNumber(n) {
  return Math.floor(Math.random() * n);
}

function populateSet() {
  currentWords.add("dashi");
  currentWords.add("miso");
  currentWords.add("tofu");
  currentWords.add("tempura");
  currentWords.add("ramen");
  currentWords.add("sake");
  currentWords.add("soba");
  currentWords.add("umami");
  currentWords.add("wasabi");
}

function constructGrid() {
  console.log("Constructing grid...");
  grid = Array.from({ length: rows }, () => Array(columns).fill("-"));
  console.log("Grid constructed...");
}

function fillGrid() {
  console.log("Filling grid...");
  for (let i = 0; i < rows; i++) {
    for (let j = 0; j < columns; j++) {
      if (grid[i][j] === "-") {
        grid[i][j] = String.fromCharCode(97 + generateRandomNumber(26));
      }
    }
  }
  console.log("Grid filled...");
}

function printGrid() {
  console.log("Printing grid...");
  for (let i = 0; i < rows; i++) {
    console.log(grid[i].join(" "));
  }
  console.log("Grid printed...");
}

function isValid(r, c) {
  return r >= 0 && r < rows && c >= 0 && c < columns && grid[r][c] === "-";
}

function dfs(r, c, word, idx) {
  if (idx === word.length) return true;

  if (!isValid(r, c)) return false;

  grid[r][c] = word[idx];
  console.log(`row: ${r} col: ${c} letter: ${word[idx]}`);

  let directions = Array.from({ length: dr.length }, (_, i) => i);
  directions = directions.sort(() => Math.random() - 0.5);

  for (let j of directions) {
    let newR = r + dr[j];
    let newC = c + dc[j];

    if (dfs(newR, newC, word, idx + 1)) {
      return true;
    }
  }

  grid[r][c] = "-";
  return false;
}

function main() {
  populateSet();
  constructGrid();
  let words = Array.from(currentWords);
  words.sort(() => Math.random() - 0.5);

  for (let i = 0; i < 3; i++) {
    console.log(`Word: ${words[i]}`);

    let wordPlaced = false;
    let r = generateRandomNumber(rows);
    let c = generateRandomNumber(columns);
    if (grid[r][c] === "-") {
      wordPlaced = dfs(r, c, words[i], 0);
    }

    if (!wordPlaced) {
      console.log(`Failed to place word: ${words[i]}`);
    }
  }

  fillGrid();
  printGrid();
}

main();
