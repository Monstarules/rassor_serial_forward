from setuptools import setup

package_name = 'rassor_serial_fwd'

setup(
    name=package_name,
    version='1.0.0',
    packages=[package_name],
    package_dir={"" : "source"},
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Monstarules',
    maintainer_email='oschyberg97@knights.ucf.edu',
    description='RE-RASSOR Subscriber for the serial communications',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'forward = rassor_serial_fwd.rassor_driver_subscriber:main',
        ],
    },
)
