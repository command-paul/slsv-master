from distutils.core import setup

setup(
    name='slsv',
    version='0.0.1',
    description='The Shakti Lockstep Verification Framework Command and Control Server',
    author='Paul George',
    author_email='pg456@snu.edu.in',
    packages=['slsv'],
    url='https://github.com/command-paul/slsv-master',
    package_data={'slsv':['*.so']},
    license='IIT - Madras Licence',
)
