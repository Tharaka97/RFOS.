# Restaurant Food Ordering System (RFOS) v1.0

RFOS is a console-based C++17 restaurant ordering application implemented from the SEP401 Software Design Specification.

## Implemented features

1. View restaurant menu
2. Place an order
3. Modify an active order
4. View the current order and running subtotal
5. Calculate bill, apply 10% GST, display an itemised receipt, and complete checkout
6. Cancel the active order with confirmation
7. Add and remove menu items during the current session
8. Centralised validation and safe recovery from invalid console input

## Architecture

The project follows the SDS three-layer design:

- **Presentation:** `ConsoleUI` and `main.cpp`
- **Business logic:** `Menu`, `MenuItem`, `Order`, `OrderItem`, `Bill`, `InputHandler`
- **Data:** in-memory `std::vector` collections

No database, file persistence, network service, or third-party library is used.

## Project structure

```text
RFOS/
├─ include/
│  ├─ bill.h
│  ├─ consoleui.h
│  ├─ inputhandler.h
│  ├─ menu.h
│  ├─ menuitem.h
│  ├─ order.h
│  └─ orderitem.h
├─ src/
│  ├─ bill.cpp
│  ├─ consoleui.cpp
│  ├─ inputhandler.cpp
│  ├─ main.cpp
│  ├─ menu.cpp
│  ├─ menuitem.cpp
│  ├─ order.cpp
│  └─ orderitem.cpp
├─ tests/
│  └─ rfos_tests.cpp
├─ .vscode/
│  ├─ extensions.json
│  ├─ launch.json
│  └─ tasks.json
├─ CMakeLists.txt
├─ .gitignore
└─ README.md
```

## Requirements

- C++17 compiler
- CMake 3.16+
- VS Code recommended extensions:
  - Microsoft C/C++ (`ms-vscode.cpptools`)
  - CMake Tools (`ms-vscode.cmake-tools`)

## Build in VS Code

1. Open the `RFOS` folder in VS Code.
2. Install the recommended extensions when prompted.
3. Open **Terminal > Run Build Task** or press `Ctrl+Shift+B`.
4. The CMake configure/build tasks create the executable in `build/`.
5. Run from the terminal:
   - Linux/macOS/MinGW: `./build/rfos`
   - Windows Visual Studio generator: `.\build\Debug\rfos.exe`

You can also use **Run and Debug** and select the matching RFOS debug configuration.

## Build manually

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Then run:

```bash
./build/rfos
```

## GitHub upload

If you create an empty GitHub repository named `RFOS`, from this folder run:

```bash
git init
git add .
git commit -m "Initial RFOS implementation from SDS"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/RFOS.git
git push -u origin main
```

## Notes

- Data is held only in memory and is lost when the application exits.
- Menu item IDs are assigned automatically for new items.
- Prices use `double` because this is what the SDS specifies. A production POS system should normally use integer cents or a decimal currency type.
- GST is calculated as `subtotal * 0.10` and displayed separately.
