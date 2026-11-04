#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
"""Compile and execute policy tests; no dependency downloads or hardware access."""
from pathlib import Path
import argparse, os, shutil, subprocess
p=argparse.ArgumentParser();p.add_argument('--cc',default=os.environ.get('CC','cc'));p.add_argument('--cxx',default=os.environ.get('CXX','c++'));a=p.parse_args()
root=Path(__file__).resolve().parents[1];build=root/'build-tests';build.mkdir(exist_ok=True)
suffix='.exe'if os.name=='nt'else''
def run(args):subprocess.run([str(x)for x in args],cwd=root,check=True)
# Static runtime on Windows keeps test execution independent of compiler PATH.
extra=['-static']if os.name=='nt'else[]
policy=build/('policy_tests'+suffix);registry=build/('controller_order_tests'+suffix)
run([a.cxx,'-std=c++11','-Wall','-Wextra','-Werror','-Iinclude','tests/test_policies.cpp',*extra,'-o',policy]);run([policy])
run([a.cc,'-std=c99','-Wall','-Wextra','-Werror','-Iinclude','-Itests/sdl_stub','src/ControllerIdentity.c','tests/test_controller_order.c',*extra,'-o',registry]);run([registry])
