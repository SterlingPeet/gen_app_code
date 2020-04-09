Readme file for the gen_app_code script.

This script will generate the base code, including the CFE table definitions, if specified, 
for the new application specified in the command.

1. Go to your $CFS_MISSION/tools/gen_app_code directory
2. Execute the Python script, gen_app_code.py.
3. Follow the usage description to generate the base code for your new applications.  
   
   Ex:  python gen_app_code.py MISSION myProj OWNER "Jane Smith" APP foo OUTDIR /home/jsmith/projA/apps
        python gen_app_code.py MISSION myProj OWNER "John Smith" APP bar TBL iloads OUTDIR .
   
NOTE: Pay close attention to how & what you name your applications at this step since 
the specified application names will be used as part of the file names, function names, 
variable names and macro names through out the code from hereon. The application file
names will be in all lowercase. In the code, it will be in all uppercase.

