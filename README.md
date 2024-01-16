# TCP_CHAT
<p>This is an ongoing project of mine. As of now, it is undergoing early development.</p>

Contribute if you want, don't if you don't.


### Prerequisites
- CMake v3.20 or later.
- GCC v13.0.0 (or Clang-16) and Make v4.4.0. (Later versions should also work.)
- A Linux computer or WSL.
- libsodium.
- OpenSSL
- git

## How-Tos

### Installing the prerequisites
- If you wish to use Clang instead of GCC, just replace 'gcc' with 'clang' on whichever command is relevant to your distribution.
- Debian and Debian-based
    - Update the package lists with `sudo apt-get update`, this also applies to Ubuntu
    - `sudo apt-get install git gcc make cmake libsodium-dev libssl-dev`
        - or, on Ubuntu and variants, `sudo apt install git gcc make cmake libsodium-dev libssl-dev`
- RHEL and Fedora-based
    - `sudo dnf install git gcc make cmake libsodium-devel openssl-devel`
- Arch Linux
    - `sudo pacman -Syu git gcc make cmake libsodium openssl`
- Windows Subsystem for Linux (WSL):
    - Follow the Linux installation instructions relevant to your WSL distribution.

### Compiling and running the project from source
1. Once the prerequisites are installed, you download the source code by clicking on "Code" and then click "Download ZIP".
    - Or, on WSL, you should just clone the repository with `git clone https://github.com/TaxEvaderKet/tcp_chat`
3. Then, you unzip the ZIP file, and `cd` into the directory it was extracted to.
    - `cd` into the directory if you opted to clone the repo instead.
5. Ensure that you are in the directory and run `cmake .`.
6. After that's done, you compile the project by running `make`.
7. Once finished compiling, you can simply run `./bin/app` and test out what is available right now.

Note that to change the compiler, you must pass in `-DCMAKE_C_COMPILER=/path/to/your/compiler`. 

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
