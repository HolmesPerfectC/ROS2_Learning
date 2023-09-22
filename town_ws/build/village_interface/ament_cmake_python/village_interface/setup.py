from setuptools import find_packages
from setuptools import setup

setup(
    name='village_interface',
    version='0.0.0',
    packages=find_packages(
        include=('village_interface', 'village_interface.*')),
)
