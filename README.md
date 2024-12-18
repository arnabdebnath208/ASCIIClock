# ASCII Clock

A simple ASCII art clock implemented in C.

## Features

- Displays current time in ASCII art
- Customizable colors
- Lightweight and easy to use

## Installation

```bash
git clone https://github.com/arnabdebnath208/asciiclock.git
cd asciiclock/src/C
make
```

## Usage

```bash
cd asciiclock/src/C
./asciiclock

# To display help
./asciiclock --help

# To change background color
./asciiclock -b <color>

# To change digit color
./asciiclock -d <color>

# To change separator color
./asciiclock --colon-color <color>

# To change weekday color
./asciiclock -w <color>

# To change date color
./asciiclock -d <color>

# To change month color
./asciiclock -m <color>

# To change year color
./asciiclock -y <color>

# All color options <color> : Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, DarkGray, LightRed, LightGreen, LightYellow, LightBlue, LightMagenta, LightCyan, LightWhite

```

## Screenshots

![Screenshot 1](images/screenshot1.png)
![Screenshot 2](images/screenshot2.png)

## Screen Recording

![Screen Recording](images/screencast1.gif)


## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin feature/your-feature`)
5. Create a new Pull Request

## License

This project is licensed under the GPL-3.0 - see the [LICENSE](LICENSE) file for details.