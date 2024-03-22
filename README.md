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
