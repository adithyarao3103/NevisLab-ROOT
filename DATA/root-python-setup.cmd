###############################################
# Submit description file for root-python-setup.py
###############################################
# 
# In this example, there's no shell script.
# The python program will set up the environment.

# The "executable", "input", and the list in transfer_input_files are
# always copied by condor. It will look in the directory "initialdir"
# for these files. If there's no initialdir, it will look in the
# directory from which you submit the job.

# The shell script that will organize the environment.
executable     = root-python-setup.py

# For this example, there are no other files to transfer.
#transfer_input_files = 

# For this example, there is no 'input' file.
#input          = root-python-setup.data

# The arguments to the executable. If you look at 
# root-python-setup.py, you'll see that it expects
# two arguments, with options. 
arguments      = -m $(Process) -o root-python-setup-test-$(Process).root

# Leave these unchanged. 
universe       = vanilla
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

# Requirements are a restriction on what kinds of machines can run
# your job. Here's an example; it means to make sure the job runs on a
# 64-bit computer.
requirements = ( Arch == "X86_64" )

# You always want to specify where the program's
# text output will go, where its error messages
# will go, and where condor's log messages will go.
output         = root-python-setup-test-$(Process).out
error          = root-python-setup-test-$(Process).err
log            = root-python-setup-test-$(Process).log

# This keeps you from getting 10,000 emails if you submit 10,000
# jobs... unless each of those 10,000 jobs crash!
notification   = Error
     
# The number following "queue" is how many times this process will be
# submitted to condor. The value of $(Process) will be 0 for the first
# process, 1 for the second, etc.  
queue
