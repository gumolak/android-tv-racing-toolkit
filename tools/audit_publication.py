#!/usr/bin/env python3
# SPDX-License-Identifier: MIT
"""Check the frozen publication allowlist, hashes and obvious private-data patterns.
This is a technical release guard, not a copyright/legal determination.
"""
from pathlib import Path
import hashlib,json,re,struct,sys,xml.etree.ElementTree as ET
ROOT=Path(__file__).resolve().parents[1]
APPROVED=['.github/workflows/test.yml', '.gitignore', 'CMakeLists.txt', 'LICENSE', 'PROVENANCE.md', 'PUBLICATION_MANIFEST.json', 'README.cs.md', 'README.md', 'docs/INTEGRATION.md', 'docs/TEST_RESULTS.md', 'docs/images/controller-routing.png', 'docs/images/controller-routing.svg', 'docs/images/timing-policies.png', 'docs/images/timing-policies.svg', 'examples/bind_two_controllers.c', 'include/racing_toolkit/ControllerIdentity.h', 'include/racing_toolkit/MenuConfirmMask.h', 'include/racing_toolkit/RandomArrival.h', 'include/racing_toolkit/StopRamp.h', 'src/ControllerIdentity.c', 'tests/sdl_stub/SDL2/SDL.h', 'tests/test_controller_order.c', 'tests/test_policies.cpp', 'tools/audit_publication.py', 'tools/run_tests.py']
actual={p.relative_to(ROOT).as_posix()for p in ROOT.rglob('*')if p.is_file()and not any(part=='.git'or part.startswith('build')or part=='__pycache__'for part in p.relative_to(ROOT).parts)}
if actual!=set(APPROVED):raise SystemExit('Allowlist mismatch: '+repr(sorted(actual.symmetric_difference(APPROVED))))
patterns=[r'gh[pousr]_[A-Za-z0-9]{20,}',r'github_pat_[A-Za-z0-9_]{20,}',r'-----BEGIN (?:RSA |OPENSSH |EC )?PRIVATE KEY-----',r'(?i)\b(?:[0-9a-f]{2}:){5}[0-9a-f]{2}\b',r'\b(?:[0-9]{1,3}\.){3}[0-9]{1,3}\b',r'[A-Z]:\\(?:Users|Windows|Program Files)\\',r'\b[0-9a-fA-F]{40}\b']
for name in APPROVED:
 p=ROOT/name
 if p.suffix=='.png':
  b=p.read_bytes();assert b[:8]==b'\x89PNG\r\n\x1a\n'and struct.unpack('>II',b[16:24])==(1400,800),name
  continue
 text=p.read_text(encoding='utf8')
 for expression in patterns:
  if re.search(expression,text):raise SystemExit('Potential private material: '+name)
 if p.suffix in('.c','.h','.cpp')and re.search(r'Game::_sub_|dword_[0-9A-Fa-f]{6}|byte_[0-9A-Fa-f]{6}',text):raise SystemExit('Engine-specific code: '+name)
 if p.suffix=='.svg':
  for element in ET.fromstring(text).iter():
   if element.tag.split('}')[-1]in('script','foreignObject','image'):raise SystemExit('Unexpected SVG element: '+name)
   if any(k.split('}')[-1]=='href'for k in element.attrib):raise SystemExit('External SVG reference: '+name)
manifest=json.loads((ROOT/'PUBLICATION_MANIFEST.json').read_text(encoding='utf8'))
expected=set(APPROVED)-{'PUBLICATION_MANIFEST.json'}
if set(manifest['files'])!=expected:raise SystemExit('Manifest paths mismatch')
for name,record in manifest['files'].items():
 data=(ROOT/name).read_bytes()
 if len(data)!=record['bytes']or hashlib.sha256(data).hexdigest()!=record['sha256']:raise SystemExit('Hash mismatch: '+name)
print('Publication audit PASS: '+str(len(APPROVED))+' allowlisted files, no executable or game binaries, game assets, device identifiers or credentials detected.')
