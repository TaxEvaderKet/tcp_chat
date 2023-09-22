# TCP_CHAT
<p>This is an ongoing project of mine. As of now, it is undergoing early development.</p>
<p>What I'm hoping to achieve is a functioning chatting application with the following features:</p>

- Secure password hashing using libsodium/argon2id.
- An OK (or better)-looking TUI.
- Channels.
- @mentioning users.

<p>What I have made so far:</p>

- Secure password hashing and data storage.

Contribute if you want, don't if you don't.


### Prerequisites
- CMake v3.2 or later.
- GCC and Make, v13.0.0 and v4.4.0 (or later) respectively.
- A Linux computer or WSL.
- libsodium.

## How-Tos

### Installing the prerequisites
- Debian and Debian-based 
    - `sudo apt-get install gcc make cmake libsodium-dev`
        - or, on Ubuntu and variants, `sudo apt install gcc make cmake libsodium-dev`
- RHEL and Fedora-based
    - `sudo dnf install gcc make cmake libsodium-devel`
- Arch Linux
    - `sudo pacman -S gcc make cmake libsodium`
- Windows Subsystem for Linux (WSL):
    - Follow the Linux installation instructions relevant to your WSL distribution.

### Compiling and running the project from source
1. Once the prerequisites are installed, you download the source code by clicking on "Code" and then click "Download ZIP".
2. Then, you unzip the ZIP file, and `cd` into the directory it was extracted to.
3. Ensure that you are in the directory and run `cmake .`.
4. After that's done, you compile the project by running `make`.
5. Once finished compiling, you can simply run `./bin/tcp_chat` and test out what is available right now.

## Contributing

### What you can do

- **Refactoring:** Help improve code quality and readability.
- **Work on custom libraries:** either improve on a pre-existing library or create a new one.
- **Edit the README:** Contribute by editing the README in a meaningful way.
- **Contribute to the Source Code:** feel free to contribute to the codebase by editing pretty much anything in src and include.

### "How do I contribute?"
1. Fork the repository
    - by clicking the "Fork" button in the top right.

2. Clone your fork to your local machine
    - Open your terminal
    - Run `git clone https://github.com/your-username/tcp_chat.git`, make sure to replace "your-username" with your GitHub username.

3. Create a new branch
    - `cd tcp_chat`
    - `git checkout -b feature-name`

4. Make your changes
    - Make your changes to the codebase. You can add new features, fix bugs, or make improvements.
    - Make sure that your changes follow coding conventions and maintain code readability.
        - Regarding coding conventions, just adapt to the already existing code in the codebase.
            - This includes adding documentation if necessary.

5. Test your changes
    - By checking outputs and handling different cases, then, if there's something to fix, do so.

6. Commit your changes
    - `git commit -m "add feature: description"`

7. Push your changes
    - `git push origin feature-name`

8. Create a pull request
    - Go to your forked repository.
    - Click the "Compare & pull request" button.
    - Review your changes and provide a clear description of what the changes add.

9. Wait for review and feedback

10. Merge your contribution

**Congrats. You've contributed.**
