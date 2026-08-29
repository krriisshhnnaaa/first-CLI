from setuptools import setup

setup(
    name='pyc-calc',
    version='1.0',
    py_modules=['pyc'],
    entry_points={
        'console_scripts': [
            'pyc = pyc:main',
        ],
    },
)
