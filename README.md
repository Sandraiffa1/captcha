# Captcha Program

An interactive C++ application using the SFML library that implements a captcha protection for closing the window. The program generates a random captcha of five letters, prompts the user to enter it, and closes only when the input matches.

## Features

- **Captcha Generation**: 
  - 5 random uppercase English letters (A–Z).
  - Each letter has a random size, color, and rotation within ±30°.
  - Letters are evenly spaced horizontally and centered vertically within the window.

- **User Input**:
  - Displayed in the top‑left corner in red.
  - Only English letters (A–Z, a–z) are accepted, thanks to `sf::Event::TextEntered` handling.
  - Backspace removes the last character.
  - Enter compares the entered text with the captcha:
    - If they match, the window closes.
    - If not, the input is cleared and a new captcha is generated.

- **System Event Handling**:
  - On window close attempt (`sf::Event::Closed`) or window resize (`sf::Event::Resized`), the input is cleared and the captcha is regenerated.
  - On resize, the view (`sf::View`) is adjusted to match the new window size, ensuring correct display.

- **Resource Management**:
  - The font is loaded via a singleton, guaranteeing a single instance of `sf::Font` from the `assets` folder.

- **CMake‑based Project**:
  - Statically links SFML 3.0.2 using FetchContent.
  - Automatically copies the `assets` directory to the build directory.

## Requirements

- C++17 compatible compiler (e.g., GCC, Clang, MSVC).
- CMake 3.15 or higher.
- SFML library (will be fetched automatically via FetchContent).

## Building and Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Sandraiffa1/captcha-program.git
   cd captcha-program
