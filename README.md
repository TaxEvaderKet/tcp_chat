# TCP_CHAT
<p>This is a very unfinished little project of mine.</p>
Contribute if you want, don't if you don't.

## Prerequisites
- GCC and Make, latest version
- A Linux computer or WSL
- libsodium

## Installing libsodium
- Debian and Debian-based 
    - `sudo apt-get install libsodium-dev` or `sudo apt install libsodium-dev`
- RHEL and Fedora-based
    - `sudo dnf install libsodium-devel`
- Arch Linux
    - `sudo pacman -S libsodium`

## Installing GCC and GNU Make
- Debian and Debian-based 
    - `sudo apt-get install gcc make` or `sudo apt install gcc make`
- RHEL and Fedora-based
    - `sudo dnf install gcc make`
- Arch Linux
    - `sudo pacman -S gcc make`

## Contributing

### What you can and can't do

- Refactoring: Help improve code quality and readability.
- Work on custom libraries: either improve on a pre-existing library or create a new one.
- Edit the README: Contribute by editing the README in a meaningful way.
- Contribute to the Source Code: feel free to contribute to the codebase by editing pretty much anything in src and include.

- (You can't) Edit the Makefile: I maintain it myself. If you find an issue, let me know.
- (Neither can you) Edit .gitignore: This is self-explanatory.

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

5. Test your changes
    - I needn't say anything about this.

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
