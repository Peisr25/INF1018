
bufbomb:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64 
  401004:	48 83 ec 08          	sub    $0x8,%rsp
  401008:	48 8b 05 e9 2f 00 00 	mov    0x2fe9(%rip),%rax        # 403ff8 <__gmon_start__@Base>
  40100f:	48 85 c0             	test   %rax,%rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	call   *%rax
  401016:	48 83 c4 08          	add    $0x8,%rsp
  40101a:	c3                   	ret    

Disassembly of section .plt:

0000000000401020 <puts@plt-0x10>:
  401020:	ff 35 e2 2f 00 00    	push   0x2fe2(%rip)        # 404008 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 e4 2f 00 00    	jmp    *0x2fe4(%rip)        # 404010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <puts@plt>:
  401030:	ff 25 e2 2f 00 00    	jmp    *0x2fe2(%rip)        # 404018 <puts@GLIBC_2.2.5>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401040 <printf@plt>:
  401040:	ff 25 da 2f 00 00    	jmp    *0x2fda(%rip)        # 404020 <printf@GLIBC_2.2.5>
  401046:	68 01 00 00 00       	push   $0x1
  40104b:	e9 d0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401050 <strcmp@plt>:
  401050:	ff 25 d2 2f 00 00    	jmp    *0x2fd2(%rip)        # 404028 <strcmp@GLIBC_2.2.5>
  401056:	68 02 00 00 00       	push   $0x2
  40105b:	e9 c0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401060 <signal@plt>:
  401060:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 404030 <signal@GLIBC_2.2.5>
  401066:	68 03 00 00 00       	push   $0x3
  40106b:	e9 b0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401070 <exit@plt>:
  401070:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 404038 <exit@GLIBC_2.2.5>
  401076:	68 04 00 00 00       	push   $0x4
  40107b:	e9 a0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401080 <getc@plt>:
  401080:	ff 25 ba 2f 00 00    	jmp    *0x2fba(%rip)        # 404040 <getc@GLIBC_2.2.5>
  401086:	68 05 00 00 00       	push   $0x5
  40108b:	e9 90 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .text:

0000000000401090 <_start>:
  401090:	f3 0f 1e fa          	endbr64 
  401094:	31 ed                	xor    %ebp,%ebp
  401096:	49 89 d1             	mov    %rdx,%r9
  401099:	5e                   	pop    %rsi
  40109a:	48 89 e2             	mov    %rsp,%rdx
  40109d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4010a1:	50                   	push   %rax
  4010a2:	54                   	push   %rsp
  4010a3:	45 31 c0             	xor    %r8d,%r8d
  4010a6:	31 c9                	xor    %ecx,%ecx
  4010a8:	48 c7 c7 21 13 40 00 	mov    $0x401321,%rdi
  4010af:	ff 15 3b 2f 00 00    	call   *0x2f3b(%rip)        # 403ff0 <__libc_start_main@GLIBC_2.34>
  4010b5:	f4                   	hlt    

00000000004010b6 <.annobin_abi_note.c>:
  4010b6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  4010bd:	00 00 00 

00000000004010c0 <_dl_relocate_static_pie>:
  4010c0:	f3 0f 1e fa          	endbr64 
  4010c4:	c3                   	ret    

00000000004010c5 <.annobin__dl_relocate_static_pie.end>:
  4010c5:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  4010cc:	00 00 00 
  4010cf:	90                   	nop

00000000004010d0 <deregister_tm_clones>:
  4010d0:	b8 50 40 40 00       	mov    $0x404050,%eax
  4010d5:	48 3d 50 40 40 00    	cmp    $0x404050,%rax
  4010db:	74 13                	je     4010f0 <deregister_tm_clones+0x20>
  4010dd:	b8 00 00 00 00       	mov    $0x0,%eax
  4010e2:	48 85 c0             	test   %rax,%rax
  4010e5:	74 09                	je     4010f0 <deregister_tm_clones+0x20>
  4010e7:	bf 50 40 40 00       	mov    $0x404050,%edi
  4010ec:	ff e0                	jmp    *%rax
  4010ee:	66 90                	xchg   %ax,%ax
  4010f0:	c3                   	ret    
  4010f1:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4010f8:	00 00 00 00 
  4010fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401100 <register_tm_clones>:
  401100:	be 50 40 40 00       	mov    $0x404050,%esi
  401105:	48 81 ee 50 40 40 00 	sub    $0x404050,%rsi
  40110c:	48 89 f0             	mov    %rsi,%rax
  40110f:	48 c1 ee 3f          	shr    $0x3f,%rsi
  401113:	48 c1 f8 03          	sar    $0x3,%rax
  401117:	48 01 c6             	add    %rax,%rsi
  40111a:	48 d1 fe             	sar    %rsi
  40111d:	74 11                	je     401130 <register_tm_clones+0x30>
  40111f:	b8 00 00 00 00       	mov    $0x0,%eax
  401124:	48 85 c0             	test   %rax,%rax
  401127:	74 07                	je     401130 <register_tm_clones+0x30>
  401129:	bf 50 40 40 00       	mov    $0x404050,%edi
  40112e:	ff e0                	jmp    *%rax
  401130:	c3                   	ret    
  401131:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401138:	00 00 00 00 
  40113c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401140 <__do_global_dtors_aux>:
  401140:	f3 0f 1e fa          	endbr64 
  401144:	80 3d 0d 2f 00 00 00 	cmpb   $0x0,0x2f0d(%rip)        # 404058 <completed.0>
  40114b:	75 13                	jne    401160 <__do_global_dtors_aux+0x20>
  40114d:	55                   	push   %rbp
  40114e:	48 89 e5             	mov    %rsp,%rbp
  401151:	e8 7a ff ff ff       	call   4010d0 <deregister_tm_clones>
  401156:	c6 05 fb 2e 00 00 01 	movb   $0x1,0x2efb(%rip)        # 404058 <completed.0>
  40115d:	5d                   	pop    %rbp
  40115e:	c3                   	ret    
  40115f:	90                   	nop
  401160:	c3                   	ret    
  401161:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401168:	00 00 00 00 
  40116c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401170 <frame_dummy>:
  401170:	f3 0f 1e fa          	endbr64 
  401174:	eb 8a                	jmp    401100 <register_tm_clones>

0000000000401176 <valid>:
  401176:	55                   	push   %rbp
  401177:	48 89 e5             	mov    %rsp,%rbp
  40117a:	48 83 ec 10          	sub    $0x10,%rsp
  40117e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  401182:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401186:	be 10 20 40 00       	mov    $0x402010,%esi
  40118b:	48 89 c7             	mov    %rax,%rdi
  40118e:	e8 bd fe ff ff       	call   401050 <strcmp@plt>
  401193:	85 c0                	test   %eax,%eax
  401195:	0f 94 c0             	sete   %al
  401198:	0f b6 c0             	movzbl %al,%eax
  40119b:	c9                   	leave  
  40119c:	c3                   	ret    

000000000040119d <danger>:
  40119d:	55                   	push   %rbp
  40119e:	48 89 e5             	mov    %rsp,%rbp
  4011a1:	bf 1a 20 40 00       	mov    $0x40201a,%edi
  4011a6:	e8 85 fe ff ff       	call   401030 <puts@plt>
  4011ab:	bf 38 20 40 00       	mov    $0x402038,%edi
  4011b0:	e8 7b fe ff ff       	call   401030 <puts@plt>
  4011b5:	90                   	nop
  4011b6:	5d                   	pop    %rbp
  4011b7:	c3                   	ret    

00000000004011b8 <protect>:
  4011b8:	55                   	push   %rbp
  4011b9:	48 89 e5             	mov    %rsp,%rbp
  4011bc:	48 83 ec 10          	sub    $0x10,%rsp
  4011c0:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  4011c4:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  4011c8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  4011cc:	48 89 c7             	mov    %rax,%rdi
  4011cf:	e8 a2 ff ff ff       	call   401176 <valid>
  4011d4:	85 c0                	test   %eax,%eax
  4011d6:	74 11                	je     4011e9 <protect+0x31>
  4011d8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  4011dc:	48 89 c7             	mov    %rax,%rdi
  4011df:	b8 00 00 00 00       	mov    $0x0,%eax
  4011e4:	e8 b4 ff ff ff       	call   40119d <danger>
  4011e9:	90                   	nop
  4011ea:	c9                   	leave  
  4011eb:	c3                   	ret    

00000000004011ec <smoke>:
  4011ec:	55                   	push   %rbp
  4011ed:	48 89 e5             	mov    %rsp,%rbp
  4011f0:	bf 61 20 40 00       	mov    $0x402061,%edi
  4011f5:	e8 36 fe ff ff       	call   401030 <puts@plt>
  4011fa:	bf 00 00 00 00       	mov    $0x0,%edi
  4011ff:	e8 6c fe ff ff       	call   401070 <exit@plt>

0000000000401204 <fizz>:
  401204:	55                   	push   %rbp
  401205:	48 89 e5             	mov    %rsp,%rbp
  401208:	48 83 ec 10          	sub    $0x10,%rsp
  40120c:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40120f:	81 7d fc 04 03 02 01 	cmpl   $0x1020304,-0x4(%rbp)
  401216:	75 16                	jne    40122e <fizz+0x2a>
  401218:	8b 45 fc             	mov    -0x4(%rbp),%eax
  40121b:	89 c6                	mov    %eax,%esi
  40121d:	bf 7c 20 40 00       	mov    $0x40207c,%edi
  401222:	b8 00 00 00 00       	mov    $0x0,%eax
  401227:	e8 14 fe ff ff       	call   401040 <printf@plt>
  40122c:	eb 14                	jmp    401242 <fizz+0x3e>
  40122e:	8b 45 fc             	mov    -0x4(%rbp),%eax
  401231:	89 c6                	mov    %eax,%esi
  401233:	bf a0 20 40 00       	mov    $0x4020a0,%edi
  401238:	b8 00 00 00 00       	mov    $0x0,%eax
  40123d:	e8 fe fd ff ff       	call   401040 <printf@plt>
  401242:	bf 00 00 00 00       	mov    $0x0,%edi
  401247:	e8 24 fe ff ff       	call   401070 <exit@plt>

000000000040124c <Gets>:
  40124c:	55                   	push   %rbp
  40124d:	48 89 e5             	mov    %rsp,%rbp
  401250:	48 83 ec 20          	sub    $0x20,%rsp
  401254:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
  401258:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  40125c:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  401260:	eb 11                	jmp    401273 <Gets+0x27>
  401262:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401266:	48 8d 50 01          	lea    0x1(%rax),%rdx
  40126a:	48 89 55 f8          	mov    %rdx,-0x8(%rbp)
  40126e:	8b 55 f4             	mov    -0xc(%rbp),%edx
  401271:	88 10                	mov    %dl,(%rax)
  401273:	48 8b 05 e6 2d 00 00 	mov    0x2de6(%rip),%rax        # 404060 <infile>
  40127a:	48 89 c7             	mov    %rax,%rdi
  40127d:	e8 fe fd ff ff       	call   401080 <getc@plt>
  401282:	89 45 f4             	mov    %eax,-0xc(%rbp)
  401285:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%rbp)
  401289:	74 06                	je     401291 <Gets+0x45>
  40128b:	83 7d f4 0a          	cmpl   $0xa,-0xc(%rbp)
  40128f:	75 d1                	jne    401262 <Gets+0x16>
  401291:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401295:	48 8d 50 01          	lea    0x1(%rax),%rdx
  401299:	48 89 55 f8          	mov    %rdx,-0x8(%rbp)
  40129d:	c6 00 00             	movb   $0x0,(%rax)
  4012a0:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4012a4:	c9                   	leave  
  4012a5:	c3                   	ret    

00000000004012a6 <bushandler>:
  4012a6:	55                   	push   %rbp
  4012a7:	48 89 e5             	mov    %rsp,%rbp
  4012aa:	48 83 ec 10          	sub    $0x10,%rsp
  4012ae:	89 7d fc             	mov    %edi,-0x4(%rbp)
  4012b1:	bf c0 20 40 00       	mov    $0x4020c0,%edi
  4012b6:	e8 75 fd ff ff       	call   401030 <puts@plt>
  4012bb:	bf e0 20 40 00       	mov    $0x4020e0,%edi
  4012c0:	e8 6b fd ff ff       	call   401030 <puts@plt>
  4012c5:	bf 00 00 00 00       	mov    $0x0,%edi
  4012ca:	e8 a1 fd ff ff       	call   401070 <exit@plt>

00000000004012cf <seghandler>:
  4012cf:	55                   	push   %rbp
  4012d0:	48 89 e5             	mov    %rsp,%rbp
  4012d3:	48 83 ec 10          	sub    $0x10,%rsp
  4012d7:	89 7d fc             	mov    %edi,-0x4(%rbp)
  4012da:	bf f8 20 40 00       	mov    $0x4020f8,%edi
  4012df:	e8 4c fd ff ff       	call   401030 <puts@plt>
  4012e4:	bf e0 20 40 00       	mov    $0x4020e0,%edi
  4012e9:	e8 42 fd ff ff       	call   401030 <puts@plt>
  4012ee:	bf 00 00 00 00       	mov    $0x0,%edi
  4012f3:	e8 78 fd ff ff       	call   401070 <exit@plt>

00000000004012f8 <illegalhandler>:
  4012f8:	55                   	push   %rbp
  4012f9:	48 89 e5             	mov    %rsp,%rbp
  4012fc:	48 83 ec 10          	sub    $0x10,%rsp
  401300:	89 7d fc             	mov    %edi,-0x4(%rbp)
  401303:	bf 20 21 40 00       	mov    $0x402120,%edi
  401308:	e8 23 fd ff ff       	call   401030 <puts@plt>
  40130d:	bf e0 20 40 00       	mov    $0x4020e0,%edi
  401312:	e8 19 fd ff ff       	call   401030 <puts@plt>
  401317:	bf 00 00 00 00       	mov    $0x0,%edi
  40131c:	e8 4f fd ff ff       	call   401070 <exit@plt>

0000000000401321 <main>:
  401321:	55                   	push   %rbp
  401322:	48 89 e5             	mov    %rsp,%rbp
  401325:	48 83 ec 10          	sub    $0x10,%rsp
  401329:	89 7d fc             	mov    %edi,-0x4(%rbp)
  40132c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
  401330:	be cf 12 40 00       	mov    $0x4012cf,%esi
  401335:	bf 0b 00 00 00       	mov    $0xb,%edi
  40133a:	e8 21 fd ff ff       	call   401060 <signal@plt>
  40133f:	be a6 12 40 00       	mov    $0x4012a6,%esi
  401344:	bf 07 00 00 00       	mov    $0x7,%edi
  401349:	e8 12 fd ff ff       	call   401060 <signal@plt>
  40134e:	be f8 12 40 00       	mov    $0x4012f8,%esi
  401353:	bf 04 00 00 00       	mov    $0x4,%edi
  401358:	e8 03 fd ff ff       	call   401060 <signal@plt>
  40135d:	48 8b 05 ec 2c 00 00 	mov    0x2cec(%rip),%rax        # 404050 <stdin@@GLIBC_2.2.5>
  401364:	48 89 05 f5 2c 00 00 	mov    %rax,0x2cf5(%rip)        # 404060 <infile>
  40136b:	b8 00 00 00 00       	mov    $0x0,%eax
  401370:	e8 11 00 00 00       	call   401386 <getbuf>
  401375:	bf 50 21 40 00       	mov    $0x402150,%edi
  40137a:	e8 b1 fc ff ff       	call   401030 <puts@plt>
  40137f:	b8 00 00 00 00       	mov    $0x0,%eax
  401384:	c9                   	leave  
  401385:	c3                   	ret    

0000000000401386 <getbuf>:
  401386:	55                   	push   %rbp
  401387:	48 89 e5             	mov    %rsp,%rbp
  40138a:	48 83 ec 20          	sub    $0x20,%rsp
  40138e:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
  401392:	48 89 c6             	mov    %rax,%rsi
  401395:	bf 74 21 40 00       	mov    $0x402174,%edi
  40139a:	b8 00 00 00 00       	mov    $0x0,%eax
  40139f:	e8 9c fc ff ff       	call   401040 <printf@plt>
  4013a4:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
  4013a8:	48 89 c7             	mov    %rax,%rdi
  4013ab:	e8 9c fe ff ff       	call   40124c <Gets>
  4013b0:	b8 01 00 00 00       	mov    $0x1,%eax
  4013b5:	c9                   	leave  
  4013b6:	c3                   	ret    

Disassembly of section .fini:

00000000004013b8 <_fini>:
  4013b8:	f3 0f 1e fa          	endbr64 
  4013bc:	48 83 ec 08          	sub    $0x8,%rsp
  4013c0:	48 83 c4 08          	add    $0x8,%rsp
  4013c4:	c3                   	ret    
