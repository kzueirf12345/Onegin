# Onegin

This is a training project. The task is to sort an array of text by lines. The example is "Onegin" (you can find source text in repo).

Only numbers and letters are taken into account in sorting.

As a result, a file is created with text
- sorted by the "direct" comparator
- sorted by the "reverse" comparator
- original

## Dependencies

### Make

Ubuntu:

```bash
sudo apt-get update
sudo apt install make
```
Windows:

[Guide](https://stackoverflow.com/questions/32127524/how-to-install-and-use-make-in-windows)

### gcc

Ubuntu:

```bash
sudo apt-get update
sudo apt install gcc
```

Windows:

[Guide](https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j)

## Usage

```bash
cd PATH/TO/DIR/Onegin/
make build
```

You can run the program ```onegin.out```. Result filename "Onegin_sort.txt".

### Make commands
- build
- start
- all
- clean
- clean_SMTH

### Debug

If you want enable debug mode, pass ```DEBUG_=1``` as a flag.