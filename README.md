# SlowCat

Like `cat` but reads file in portions. It can repeat file reading infinite.

```
Usage: slowcat [options] <input file>

Options:
  --help                this help
  -P [ --portion ] arg  portion size in bytes
  -R [ --rate ] arg     read rate in portions per second
  --repeat arg          repeat N times (0 - forever)
```

## Installation

```sh
sudo sh -c 'curl -L "https://github.com/navrocky/slowcat/releases/download/1.0.0/slowcat" -o /usr/local/bin/slowcat && chmod +x /usr/local/bin/slowcat'
```
