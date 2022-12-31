# REGISTRY
List of registries used by windows
## method
- install WPA(windows performance analyzer)
- open cmd in WPA folder and type "xbootmgr -trace boot -traceFlags REGISTRY"
- wait for prompt(delaying for boot trace) and push Finish
- you can find boot_REGISTRY_1.etl in User folder or WPA folder
- open etl file on winodws 10(installed WPA)
- duble click Registry in Graph Explorer > Storage > Registry
- select QueryValue and right click, click "Filter To Selection"
- select QueryValue and search(Ctrl+f)

### Device-Class
List of registries used by specific devices such as GPUs and NICs
### service
List of registries used by specific service
### extra
List of registries used at locations of personal interest
