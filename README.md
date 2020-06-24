# RegexInstaller
Install files by regular expression

### Install an applicaiton by an install file, the install file essentially has 3 params:
* source root path
* destination root path
* regex to match the relative paths to source root path **literally** (including empty directories)

### sample install file (json)
```
{
    "InstallItems":
    [
        {
            "SourceRoot": "path/source/root/folder",
            "DestinationRoot": "path/destinationRoot/root/folder",
            "RelativePathRegex": ".*/.txt$"
        }
    ]
}
```
