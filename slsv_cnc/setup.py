from distutils.core import setup

setup(
    name='SLSV',
    version='0.0.1',
    description='The Shakti Lockstep Verification Framework Command and Control Server',
    author='Paul George',
    author_email='pg456@snu.edu.in',
    packages=['SLSV'],
    url='https://github.com/command-paul/slsv-master',
    package_data={'SLSV':['*.so']},
    license='IIT - Madras Licence',
)