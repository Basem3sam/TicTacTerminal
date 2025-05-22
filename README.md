
# XO++ — Object-Oriented Tic-Tac-Toe Game

A polished, object-oriented Tic-Tac-Toe game written in modern C++17. Featuring both a fully styled terminal interface and an optional graphical UI using **SFML**. Supports human and AI players with a clean architecture that separates core logic from UI.

---

## 🎮 Features

- **Two Game Modes**:
  - Human vs Human
  - Human vs AI (Bot)
- **Beautiful Terminal UI**:
  - Fully colored, animated CLI experience
  - Stylish win/lose/draw announcements
- **Graphical GUI Mode** (via SFML):
  - Clickable XO board
  - Visually intuitive interface
- **Modular Architecture**:
  - Clean separation between logic, terminal UI, and GUI
  - Easily extendable and testable
- Input validation, error handling, and responsive prompts
- Cross-platform support

---

## 🛠 Requirements

- **C++17** compatible compiler (e.g., g++, clang++, MSVC)
- **CMake** (version 3.10+)
- [Optional] **SFML** (v2.5+) for GUI mode

---

## 🧱 Building the Project

1. Clone the repository:

   ```bash
   git clone https://github.com/BasemEsam/TicTacToe++.git
   cd TicTacToe++
   ```

2. Create a build directory and navigate into it:

   ```bash
   mkdir build
   cd build
   ```

3. Configure the project using CMake:

   ```bash
   cmake ..
   ```

   > To enable GUI build (if SFML is installed), add:
   >
   > ```bash
   > cmake -DENABLE_GUI=ON ..
   > ```

4. Build the game:

   ```bash
   cmake --build .
   ```

---

## ▶️ Running the Game

After building, run the game executable:

- On **Linux/macOS**:
  ```bash
  ./xo
  ```

- On **Windows**:
  ```bash
  xo.exe
  ```

> If GUI is enabled, you'll be prompted at startup to choose between **Terminal** or **Graphical** mode.

---

## 🧩 GUI Mode (SFML)

If you choose the graphical UI, you'll get:

- A resizable window with a 3x3 grid
- Clickable cell interactions
- Animated win/draw effects
- Responsive layout using SFML

Make sure **SFML** is installed and linked correctly when using GUI.

---

## 📝 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for more details.

---

## 🤝 Contributing

Feel free to fork the repo and open pull requests. Feedback, ideas, and improvements are always welcome!

---

> Enjoy playing and learning with XO++ – the ultimate terminal & GUI-based Tic-Tac-Toe experience!  
> Built with ❤️ by **Basem Esam**
