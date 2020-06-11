# tas-script
A modification of sys-script by Sorenbug to run on Lua and be more TAS focused\
Find sys-script [here](https://github.com/sorenbug/sys-script)

## Support the Creators
Join our [Discord server](http://discord.gg/qeamCcV)\
Support me on [Patreon](https://www.patreon.com/aaronhh) or [PayPal](https://www.paypal.me/aaronhamhub)\
Make a pull request!\

## Building from Source
1. [Set up the required libraries](https://switchbrew.org/wiki/Setting_up_Development_Environment)
2. In the newly installed MSYS2, navigate to the folder you'd like to build this project in, either by opening MSYS in that directory or using the `cd` command to navigate
3. `git clone https://github.com/hamhub7/tas-script.git`
4. `cd tas-script`
5. `make`
6. You should see a file called `tas-script.nsp`
\
\
Optionally, you can choose to run `make sd` to make a convenient sd card package. The command should create a folder called `sd` that you can simply drag and drop the contents of onto your sd card.

The `make` process will fail for one of three reasons:
- You cloned a commit that doesn't compile (unlikely)
- Your folder is named something other than `tas-script`; solution is to `ln -s tas-script.json config.json`
- Your directory's full path has spaces in it (usually your account name)
