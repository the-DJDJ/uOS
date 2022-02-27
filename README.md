# uOS
The repository holding the code for the usefulOS, a very basic C kernel.

uOS is a simple kernel that I started writing as a side project, using [Erik Helin and Adam Renberg](https://littleosbook.github.io/)'s guide as inspiration. It's been a great learning experience in how low-level languages work and boot. It doesn't have to be useful - it's just fun.

## Usage
To build uOS, use the Makefile:
```shell
make all
```

It can then be run with
```shell
make run
```

To export an ISO image,
```shell
make os.iso
```

## Dependencies
All of the dependencies for uOS can be installed using `apt-get`, or whichever package manager you prefer
```shell
sudo apt install build-essential nasm genisoimage bochs bochs-sdl
```
