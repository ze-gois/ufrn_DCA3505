
./build/k01_paging:     file format elf32-i386


Disassembly of section .text:

00100000 <multiboot_header>:
  100000:	02 b0 ad 1b 00 00    	add    0x1bad(%eax),%dh
  100006:	00 00                	add    %al,(%eax)
  100008:	fe 4f 52             	decb   0x52(%edi)
  10000b:	e4                 	in     $0xbc,%al

0010000c <start>:
  10000c:	bc 00 10 11 00       	mov    $0x111000,%esp
  100011:	e9 0a 03 00 00       	jmp    100320 <main>

00100016 <page_fault_entry>:
  100016:	60                   	pusha
  100017:	54                   	push   %esp
  100018:	e8 83 02 00 00       	call   1002a0 <page_fault_handler>
  10001d:	83 c4 04             	add    $0x4,%esp
  100020:	61                   	popa
  100021:	83 c4 04             	add    $0x4,%esp
  100024:	cf                   	iret
  100025:	66 90                	xchg   %ax,%ax
  100027:	66 90                	xchg   %ax,%ax
  100029:	66 90                	xchg   %ax,%ax
  10002b:	66 90                	xchg   %ax,%ax
  10002d:	66 90                	xchg   %ax,%ax
  10002f:	66 90                	xchg   %ax,%ax
  100031:	66 90                	xchg   %ax,%ax
  100033:	66 90                	xchg   %ax,%ax
  100035:	66 90                	xchg   %ax,%ax
  100037:	66 90                	xchg   %ax,%ax
  100039:	66 90                	xchg   %ax,%ax
  10003b:	66 90                	xchg   %ax,%ax
  10003d:	66 90                	xchg   %ax,%ax
  10003f:	90                   	nop

00100040 <b>:
  100040:	57                   	push   %edi
  100041:	56                   	push   %esi
  100042:	53                   	push   %ebx
  100043:	83 ec 04             	sub    $0x4,%esp
  100046:	8b 5c 24 14          	mov    0x14(%esp),%ebx
  10004a:	85 db                	test   %ebx,%ebx
  10004c:	7e 32                	jle    100080 <b+0x40>
  10004e:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
  100055:	8d 74 24 18          	lea    0x18(%esp),%esi
  100059:	31 c0                	xor    %eax,%eax
  10005b:	31 d2                	xor    %edx,%edx
  10005d:	8d 76 00             	lea    0x0(%esi),%esi
  100060:	8b 0c 86             	mov    (%esi,%eax,4),%ecx
  100063:	8b 3c 24             	mov    (%esp),%edi
  100066:	83 c0 01             	add    $0x1,%eax
  100069:	d3 e7                	shl    %cl,%edi
  10006b:	09 fa                	or     %edi,%edx
  10006d:	39 c3                	cmp    %eax,%ebx
  10006f:	75 ef                	jne    100060 <b+0x20>
  100071:	83 c4 04             	add    $0x4,%esp
  100074:	89 d0                	mov    %edx,%eax
  100076:	5b                   	pop    %ebx
  100077:	5e                   	pop    %esi
  100078:	5f                   	pop    %edi
  100079:	c3                   	ret
  10007a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  100080:	83 c4 04             	add    $0x4,%esp
  100083:	31 d2                	xor    %edx,%edx
  100085:	5b                   	pop    %ebx
  100086:	89 d0                	mov    %edx,%eax
  100088:	5e                   	pop    %esi
  100089:	5f                   	pop    %edi
  10008a:	c3                   	ret
  10008b:	66 90                	xchg   %ax,%ax
  10008d:	66 90                	xchg   %ax,%ax
  10008f:	66 90                	xchg   %ax,%ax
  100091:	66 90                	xchg   %ax,%ax
  100093:	66 90                	xchg   %ax,%ax
  100095:	66 90                	xchg   %ax,%ax
  100097:	66 90                	xchg   %ax,%ax
  100099:	66 90                	xchg   %ax,%ax
  10009b:	66 90                	xchg   %ax,%ax
  10009d:	66 90                	xchg   %ax,%ax
  10009f:	90                   	nop

001000a0 <invlpg>:
  1000a0:	8b 44 24 04          	mov    0x4(%esp),%eax
  1000a4:	0f 01 38             	invlpg (%eax)
  1000a7:	c3                   	ret
  1000a8:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000af:	00 

001000b0 <set_cr4>:
  1000b0:	8b 44 24 04          	mov    0x4(%esp),%eax
  1000b4:	0f 22 e0             	mov    %eax,%cr4
  1000b7:	c3                   	ret
  1000b8:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000bf:	00 

001000c0 <get_cr4>:
  1000c0:	0f 20 e0             	mov    %cr4,%eax
  1000c3:	c3                   	ret
  1000c4:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000cb:	00 
  1000cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001000d0 <set_cr3>:
  1000d0:	8b 44 24 04          	mov    0x4(%esp),%eax
  1000d4:	0f 22 d8             	mov    %eax,%cr3
  1000d7:	c3                   	ret
  1000d8:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000df:	00 

001000e0 <get_cr3>:
  1000e0:	0f 20 d8             	mov    %cr3,%eax
  1000e3:	c3                   	ret
  1000e4:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000eb:	00 
  1000ec:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001000f0 <get_cr2>:
  1000f0:	0f 20 d0             	mov    %cr2,%eax
  1000f3:	c3                   	ret
  1000f4:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000fb:	00 
  1000fc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100100 <set_cr0>:
  100100:	8b 44 24 04          	mov    0x4(%esp),%eax
  100104:	0f 22 c0             	mov    %eax,%cr0
  100107:	c3                   	ret
  100108:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10010f:	00 

00100110 <get_cr0>:
  100110:	0f 20 c0             	mov    %cr0,%eax
  100113:	c3                   	ret
  100114:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10011b:	00 
  10011c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100120 <outb>:
  100120:	0f b6 44 24 04       	movzbl 0x4(%esp),%eax
  100125:	0f b7 54 24 08       	movzwl 0x8(%esp),%edx
  10012a:	ee                   	out    %al,(%dx)
  10012b:	c3                   	ret
  10012c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100130 <inb>:
  100130:	8b 54 24 04          	mov    0x4(%esp),%edx
  100134:	ec                   	in     (%dx),%al
  100135:	c3                   	ret
  100136:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10013d:	00 
  10013e:	66 90                	xchg   %ax,%ax

00100140 <putc>:
  100140:	0f b6 4c 24 04       	movzbl 0x4(%esp),%ecx
  100145:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10014a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  100150:	ec                   	in     (%dx),%al
  100151:	a8 20                	test   $0x20,%al
  100153:	74 fb                	je     100150 <putc+0x10>
  100155:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10015a:	89 c8                	mov    %ecx,%eax
  10015c:	ee                   	out    %al,(%dx)
  10015d:	c3                   	ret
  10015e:	66 90                	xchg   %ax,%ax

00100160 <puts>:
  100160:	57                   	push   %edi
  100161:	56                   	push   %esi
  100162:	53                   	push   %ebx
  100163:	8b 74 24 10          	mov    0x10(%esp),%esi
  100167:	0f b6 1e             	movzbl (%esi),%ebx
  10016a:	84 db                	test   %bl,%bl
  10016c:	74 1f                	je     10018d <puts+0x2d>
  10016e:	66 90                	xchg   %ax,%ax
  100170:	ba fd 03 00 00       	mov    $0x3fd,%edx
  100175:	ec                   	in     (%dx),%al
  100176:	a8 20                	test   $0x20,%al
  100178:	74 f6                	je     100170 <puts+0x10>
  10017a:	89 d8                	mov    %ebx,%eax
  10017c:	ba f8 03 00 00       	mov    $0x3f8,%edx
  100181:	ee                   	out    %al,(%dx)
  100182:	0f b6 5e 01          	movzbl 0x1(%esi),%ebx
  100186:	83 c6 01             	add    $0x1,%esi
  100189:	84 db                	test   %bl,%bl
  10018b:	75 e3                	jne    100170 <puts+0x10>
  10018d:	5b                   	pop    %ebx
  10018e:	5e                   	pop    %esi
  10018f:	5f                   	pop    %edi
  100190:	c3                   	ret
  100191:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  100198:	00 
  100199:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

001001a0 <put_hex>:
  1001a0:	e8 65 02 00 00       	call   10040a <__x86.get_pc_thunk.dx>
  1001a5:	81 c2 4b 07 00 00    	add    $0x74b,%edx
  1001ab:	57                   	push   %edi
  1001ac:	56                   	push   %esi
  1001ad:	53                   	push   %ebx
  1001ae:	83 ec 10             	sub    $0x10,%esp
  1001b1:	8b 44 24 20          	mov    0x20(%esp),%eax
  1001b5:	c6 44 24 0f 00       	movb   $0x0,0xf(%esp)
  1001ba:	85 c0                	test   %eax,%eax
  1001bc:	0f 84 c5 00 00 00    	je     100287 <put_hex+0xe7>
  1001c2:	8d 5c 24 0e          	lea    0xe(%esp),%ebx
  1001c6:	8d ba 93 fc ff ff    	lea    -0x36d(%edx),%edi
  1001cc:	89 d9                	mov    %ebx,%ecx
  1001ce:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1001d5:	00 
  1001d6:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1001dd:	00 
  1001de:	66 90                	xchg   %ax,%ax
  1001e0:	89 c2                	mov    %eax,%edx
  1001e2:	83 e9 01             	sub    $0x1,%ecx
  1001e5:	83 e2 0f             	and    $0xf,%edx
  1001e8:	0f b6 34 17          	movzbl (%edi,%edx,1),%esi
  1001ec:	89 f2                	mov    %esi,%edx
  1001ee:	88 51 01             	mov    %dl,0x1(%ecx)
  1001f1:	c1 e8 04             	shr    $0x4,%eax
  1001f4:	75 ea                	jne    1001e0 <put_hex+0x40>
  1001f6:	ba fd 03 00 00       	mov    $0x3fd,%edx
  1001fb:	2e 8d 74 26 00       	lea    %cs:0x0(%esi,%eiz,1),%esi
  100200:	ec                   	in     (%dx),%al
  100201:	a8 20                	test   $0x20,%al
  100203:	74 fb                	je     100200 <put_hex+0x60>
  100205:	b8 30 00 00 00       	mov    $0x30,%eax
  10020a:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10020f:	ee                   	out    %al,(%dx)
  100210:	ba fd 03 00 00       	mov    $0x3fd,%edx
  100215:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10021c:	00 
  10021d:	8d 76 00             	lea    0x0(%esi),%esi
  100220:	ec                   	in     (%dx),%al
  100221:	a8 20                	test   $0x20,%al
  100223:	74 fb                	je     100220 <put_hex+0x80>
  100225:	b8 78 00 00 00       	mov    $0x78,%eax
  10022a:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10022f:	ee                   	out    %al,(%dx)
  100230:	39 d9                	cmp    %ebx,%ecx
  100232:	74 32                	je     100266 <put_hex+0xc6>
  100234:	89 f0                	mov    %esi,%eax
  100236:	84 c0                	test   %al,%al
  100238:	74 25                	je     10025f <put_hex+0xbf>
  10023a:	8d 59 01             	lea    0x1(%ecx),%ebx
  10023d:	8d 76 00             	lea    0x0(%esi),%esi
  100240:	ba fd 03 00 00       	mov    $0x3fd,%edx
  100245:	ec                   	in     (%dx),%al
  100246:	a8 20                	test   $0x20,%al
  100248:	74 f6                	je     100240 <put_hex+0xa0>
  10024a:	89 f0                	mov    %esi,%eax
  10024c:	ba f8 03 00 00       	mov    $0x3f8,%edx
  100251:	ee                   	out    %al,(%dx)
  100252:	0f b6 73 01          	movzbl 0x1(%ebx),%esi
  100256:	83 c3 01             	add    $0x1,%ebx
  100259:	89 f0                	mov    %esi,%eax
  10025b:	84 c0                	test   %al,%al
  10025d:	75 e1                	jne    100240 <put_hex+0xa0>
  10025f:	83 c4 10             	add    $0x10,%esp
  100262:	5b                   	pop    %ebx
  100263:	5e                   	pop    %esi
  100264:	5f                   	pop    %edi
  100265:	c3                   	ret
  100266:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10026b:	2e 8d 74 26 00       	lea    %cs:0x0(%esi,%eiz,1),%esi
  100270:	ec                   	in     (%dx),%al
  100271:	a8 20                	test   $0x20,%al
  100273:	74 fb                	je     100270 <put_hex+0xd0>
  100275:	b8 30 00 00 00       	mov    $0x30,%eax
  10027a:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10027f:	ee                   	out    %al,(%dx)
  100280:	83 c4 10             	add    $0x10,%esp
  100283:	5b                   	pop    %ebx
  100284:	5e                   	pop    %esi
  100285:	5f                   	pop    %edi
  100286:	c3                   	ret
  100287:	8d 5c 24 0e          	lea    0xe(%esp),%ebx
  10028b:	31 f6                	xor    %esi,%esi
  10028d:	89 d9                	mov    %ebx,%ecx
  10028f:	e9 62 ff ff ff       	jmp    1001f6 <put_hex+0x56>
  100294:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10029b:	00 
  10029c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001002a0 <page_fault_handler>:
  1002a0:	e8 61 01 00 00       	call   100406 <__x86.get_pc_thunk.ax>
  1002a5:	05 4b 06 00 00       	add    $0x64b,%eax
  1002aa:	55                   	push   %ebp
  1002ab:	57                   	push   %edi
  1002ac:	56                   	push   %esi
  1002ad:	be 0a 00 00 00       	mov    $0xa,%esi
  1002b2:	53                   	push   %ebx
  1002b3:	8d a8 b0 fc ff ff    	lea    -0x350(%eax),%ebp
  1002b9:	8d 98 a4 fc ff ff    	lea    -0x35c(%eax),%ebx
  1002bf:	90                   	nop
  1002c0:	ba fd 03 00 00       	mov    $0x3fd,%edx
  1002c5:	ec                   	in     (%dx),%al
  1002c6:	a8 20                	test   $0x20,%al
  1002c8:	74 f6                	je     1002c0 <page_fault_handler+0x20>
  1002ca:	89 f0                	mov    %esi,%eax
  1002cc:	ba f8 03 00 00       	mov    $0x3f8,%edx
  1002d1:	ee                   	out    %al,(%dx)
  1002d2:	83 c3 01             	add    $0x1,%ebx
  1002d5:	0f b6 33             	movzbl (%ebx),%esi
  1002d8:	39 eb                	cmp    %ebp,%ebx
  1002da:	75 e4                	jne    1002c0 <page_fault_handler+0x20>
  1002dc:	eb fe                	jmp    1002dc <page_fault_handler+0x3c>
  1002de:	66 90                	xchg   %ax,%ax

001002e0 <init_idt>:
  1002e0:	e8 21 01 00 00       	call   100406 <__x86.get_pc_thunk.ax>
  1002e5:	05 0b 06 00 00       	add    $0x60b,%eax
  1002ea:	c7 80 82 17 01 00 08 	movl   $0x8f000008,0x11782(%eax)
  1002f1:	00 00 8f 
  1002f4:	c7 c2 16 00 10 00    	mov    $0x100016,%edx
  1002fa:	66 89 90 80 17 01 00 	mov    %dx,0x11780(%eax)
  100301:	c1 ea 10             	shr    $0x10,%edx
  100304:	66 89 90 86 17 01 00 	mov    %dx,0x11786(%eax)
  10030b:	0f 01 98 f8 ff ff ff 	lidtl  -0x8(%eax)
  100312:	c3                   	ret
  100313:	66 90                	xchg   %ax,%ax
  100315:	66 90                	xchg   %ax,%ax
  100317:	66 90                	xchg   %ax,%ax
  100319:	66 90                	xchg   %ax,%ax
  10031b:	66 90                	xchg   %ax,%ax
  10031d:	66 90                	xchg   %ax,%ax
  10031f:	90                   	nop

00100320 <main>:
  100320:	8d 4c 24 04          	lea    0x4(%esp),%ecx
  100324:	83 e4 f0             	and    $0xfffffff0,%esp
  100327:	ff 71 fc             	push   -0x4(%ecx)
  10032a:	55                   	push   %ebp
  10032b:	89 e5                	mov    %esp,%ebp
  10032d:	53                   	push   %ebx
  10032e:	e8 cf 00 00 00       	call   100402 <__x86.get_pc_thunk.bx>
  100333:	81 c3 bd 05 00 00    	add    $0x5bd,%ebx
  100339:	51                   	push   %ecx
  10033a:	83 ec 0c             	sub    $0xc,%esp
  10033d:	8d 83 20 fb ff ff    	lea    -0x4e0(%ebx),%eax
  100343:	50                   	push   %eax
  100344:	e8 17 fe ff ff       	call   100160 <puts>
  100349:	8d 83 58 fb ff ff    	lea    -0x4a8(%ebx),%eax
  10034f:	89 04 24             	mov    %eax,(%esp)
  100352:	e8 09 fe ff ff       	call   100160 <puts>
  100357:	8d 83 7c fb ff ff    	lea    -0x484(%ebx),%eax
  10035d:	89 04 24             	mov    %eax,(%esp)
  100360:	e8 fb fd ff ff       	call   100160 <puts>
  100365:	8d 83 b8 fb ff ff    	lea    -0x448(%ebx),%eax
  10036b:	89 04 24             	mov    %eax,(%esp)
  10036e:	e8 ed fd ff ff       	call   100160 <puts>
  100373:	6a 00                	push   $0x0
  100375:	6a 01                	push   $0x1
  100377:	6a 07                	push   $0x7
  100379:	6a 03                	push   $0x3
  10037b:	e8 c0 fc ff ff       	call   100040 <b>
  100380:	83 c4 14             	add    $0x14,%esp
  100383:	89 83 10 07 01 00    	mov    %eax,0x10710(%ebx)
  100389:	8d 83 e8 fb ff ff    	lea    -0x418(%ebx),%eax
  10038f:	50                   	push   %eax
  100390:	e8 cb fd ff ff       	call   100160 <puts>
  100395:	8d 83 10 07 01 00    	lea    0x10710(%ebx),%eax
  10039b:	89 04 24             	mov    %eax,(%esp)
  10039e:	e8 2d fd ff ff       	call   1000d0 <set_cr3>
  1003a3:	8d 83 18 fc ff ff    	lea    -0x3e8(%ebx),%eax
  1003a9:	89 04 24             	mov    %eax,(%esp)
  1003ac:	e8 af fd ff ff       	call   100160 <puts>
  1003b1:	e8 0a fd ff ff       	call   1000c0 <get_cr4>
  1003b6:	83 c8 10             	or     $0x10,%eax
  1003b9:	89 04 24             	mov    %eax,(%esp)
  1003bc:	e8 ef fc ff ff       	call   1000b0 <set_cr4>
  1003c1:	8d 83 5f fc ff ff    	lea    -0x3a1(%ebx),%eax
  1003c7:	89 04 24             	mov    %eax,(%esp)
  1003ca:	e8 91 fd ff ff       	call   100160 <puts>
  1003cf:	e8 3c fd ff ff       	call   100110 <get_cr0>
  1003d4:	0d 00 00 00 80       	or     $0x80000000,%eax
  1003d9:	89 04 24             	mov    %eax,(%esp)
  1003dc:	e8 1f fd ff ff       	call   100100 <set_cr0>
  1003e1:	8d 83 38 fc ff ff    	lea    -0x3c8(%ebx),%eax
  1003e7:	89 04 24             	mov    %eax,(%esp)
  1003ea:	e8 71 fd ff ff       	call   100160 <puts>
  1003ef:	8d 83 7a fc ff ff    	lea    -0x386(%ebx),%eax
  1003f5:	89 04 24             	mov    %eax,(%esp)
  1003f8:	e8 63 fd ff ff       	call   100160 <puts>
  1003fd:	83 c4 10             	add    $0x10,%esp
  100400:	eb fe                	jmp    100400 <main+0xe0>

00100402 <__x86.get_pc_thunk.bx>:
  100402:	8b 1c 24             	mov    (%esp),%ebx
  100405:	c3                   	ret

00100406 <__x86.get_pc_thunk.ax>:
  100406:	8b 04 24             	mov    (%esp),%eax
  100409:	c3                   	ret

0010040a <__x86.get_pc_thunk.dx>:
  10040a:	8b 14 24             	mov    (%esp),%edx
  10040d:	c3                   	ret

Disassembly of section .rodata:

00100410 <.rodata>:
  100410:	0a 3d 3d 3d 3d 3d    	or     0x3d3d3d3d,%bh
  100416:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  10041b:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  100420:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  100425:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  10042a:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  10042f:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  100434:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  100439:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  10043e:	3d 3d 3d 3d 3d       	cmp    $0x3d3d3d3d,%eax
  100443:	3d 3d 3d 0a 00       	cmp    $0xa3d3d,%eax
  100448:	31 2e                	xor    %ebp,(%esi)
  10044a:	20 50 72             	and    %dl,0x72(%eax)
  10044d:	c3                   	ret
  10044e:	a1 74 69 63 61       	mov    0x61636974,%eax
  100453:	3a 20                	cmp    (%eax),%ah
  100455:	68 61 62 69 6c       	push   $0x6c696261
  10045a:	69 74 61 72 20 70 61 	imul   $0x67617020,0x72(%ecx,%eiz,2),%esi
  100461:	67 
  100462:	69 6e 61 c3 a7 c3 a3 	imul   $0xa3c3a7c3,0x61(%esi),%ebp
  100469:	6f                   	outsl  %ds:(%esi),(%dx)
  10046a:	0a 00                	or     (%eax),%al
  10046c:	e2 97                	loop   100405 <__x86.get_pc_thunk.bx+0x3>
  10046e:	8f                   	(bad)
  10046f:	20 49 6e             	and    %cl,0x6e(%ecx)
  100472:	69 63 69 61 6c 69 7a 	imul   $0x7a696c61,0x69(%ebx),%esp
  100479:	61                   	popa
  10047a:	72 20                	jb     10049c <__x86.get_pc_thunk.dx+0x92>
  10047c:	6f                   	outsl  %ds:(%esi),(%dx)
  10047d:	73 20                	jae    10049f <__x86.get_pc_thunk.dx+0x95>
  10047f:	70 72                	jo     1004f3 <__x86.get_pc_thunk.dx+0xe9>
  100481:	69 6d 65 69 72 6f 73 	imul   $0x736f7269,0x65(%ebp),%ebp
  100488:	20 34 4d 42 20 63 6f 	and    %dh,0x6f632042(,%ecx,2)
  10048f:	6d                   	insl   (%dx),%es:(%edi)
  100490:	20 69 64             	and    %ch,0x64(%ecx)
  100493:	65 6e                	outsb  %gs:(%esi),(%dx)
  100495:	74 69                	je     100500 <__x86.get_pc_thunk.dx+0xf6>
  100497:	64 61                	fs popa
  100499:	64 65 2c 20          	fs gs sub $0x20,%al
  10049d:	76 61                	jbe    100500 <__x86.get_pc_thunk.dx+0xf6>
  10049f:	6c                   	insb   (%dx),%es:(%edi)
  1004a0:	6f                   	outsl  %ds:(%esi),(%dx)
  1004a1:	72 3a                	jb     1004dd <__x86.get_pc_thunk.dx+0xd3>
  1004a3:	0a 00                	or     (%eax),%al
  1004a5:	00 00                	add    %al,(%eax)
  1004a7:	00 e2                	add    %ah,%dl
  1004a9:	97                   	xchg   %eax,%edi
  1004aa:	8b 20                	mov    (%eax),%esp
  1004ac:	50                   	push   %eax
  1004ad:	c3                   	ret
  1004ae:	a1 67 69 6e 61       	mov    0x616e6967,%eax
  1004b3:	20 64 65 20          	and    %ah,0x20(%ebp,%eiz,2)
  1004b7:	34 4d                	xor    $0x4d,%al
  1004b9:	42                   	inc    %edx
  1004ba:	2c 20                	sub    $0x20,%al
  1004bc:	6c                   	insb   (%dx),%es:(%edi)
  1004bd:	65 69 74 75 72 61 2f 	imul   $0x73652f61,%gs:0x72(%ebp,%esi,2),%esi
  1004c4:	65 73 
  1004c6:	63 72 69             	arpl   %esi,0x69(%edx)
  1004c9:	74 61                	je     10052c <__x86.get_pc_thunk.dx+0x122>
  1004cb:	2c 20                	sub    $0x20,%al
  1004cd:	70 72                	jo     100541 <__x86.get_pc_thunk.dx+0x137>
  1004cf:	65 73 65             	gs jae 100537 <__x86.get_pc_thunk.dx+0x12d>
  1004d2:	6e                   	outsb  %ds:(%esi),(%dx)
  1004d3:	74 65                	je     10053a <__x86.get_pc_thunk.dx+0x130>
  1004d5:	0a 00                	or     (%eax),%al
  1004d7:	00 e2                	add    %ah,%dl
  1004d9:	97                   	xchg   %eax,%edi
  1004da:	8f                   	(bad)
  1004db:	20 49 6e             	and    %cl,0x6e(%ecx)
  1004de:	69 63 69 61 6c 69 7a 	imul   $0x7a696c61,0x69(%ebx),%esp
  1004e5:	61                   	popa
  1004e6:	72 20                	jb     100508 <__x86.get_pc_thunk.dx+0xfe>
  1004e8:	63 72 33             	arpl   %esi,0x33(%edx)
  1004eb:	20 70 61             	and    %dh,0x61(%eax)
  1004ee:	72 61                	jb     100551 <__x86.get_pc_thunk.dx+0x147>
  1004f0:	20 61 70             	and    %ah,0x70(%ecx)
  1004f3:	6f                   	outsl  %ds:(%esi),(%dx)
  1004f4:	6e                   	outsb  %ds:(%esi),(%dx)
  1004f5:	74 61                	je     100558 <__x86.get_pc_thunk.dx+0x14e>
  1004f7:	72 20                	jb     100519 <__x86.get_pc_thunk.dx+0x10f>
  1004f9:	70 61                	jo     10055c <__x86.get_pc_thunk.dx+0x152>
  1004fb:	72 61                	jb     10055e <__x86.get_pc_thunk.dx+0x154>
  1004fd:	20 61 20             	and    %ah,0x20(%ecx)
  100500:	72 61                	jb     100563 <__x86.get_pc_thunk.dx+0x159>
  100502:	69 7a 0a 00 00 00 e2 	imul   $0xe2000000,0xa(%edx),%edi
  100509:	97                   	xchg   %eax,%edi
  10050a:	8f                   	(bad)
  10050b:	20 48 61             	and    %cl,0x61(%eax)
  10050e:	62 69 6c             	bound  %ebp,0x6c(%ecx)
  100511:	69 74 61 72 20 70 c3 	imul   $0xa1c37020,0x72(%ecx,%eiz,2),%esi
  100518:	a1 
  100519:	67 69 6e 61 73 20 64 	imul   $0x65642073,0x61(%bp),%ebp
  100520:	65 
  100521:	20 34 4d 42 0a 00 00 	and    %dh,0xa42(,%ecx,2)
  100528:	e2 97                	loop   1004c1 <__x86.get_pc_thunk.dx+0xb7>
  10052a:	8f                   	(bad)
  10052b:	20 45 73             	and    %al,0x73(%ebp)
  10052e:	63 72 65             	arpl   %esi,0x65(%edx)
  100531:	76 65                	jbe    100598 <__x86.get_pc_thunk.dx+0x18e>
  100533:	72 20                	jb     100555 <__x86.get_pc_thunk.dx+0x14b>
  100535:	22 50 61             	and    0x61(%eax),%dl
  100538:	67 69 6e 61 c3 a7 c3 	imul   $0xa3c3a7c3,0x61(%bp),%ebp
  10053f:	a3 
  100540:	6f                   	outsl  %ds:(%esi),(%dx)
  100541:	20 68 61             	and    %ch,0x61(%eax)
  100544:	62 69 6c             	bound  %ebp,0x6c(%ecx)
  100547:	69 74 61 64 61 22 0a 	imul   $0xa2261,0x64(%ecx,%eiz,2),%esi
  10054e:	00 
  10054f:	e2 97                	loop   1004e8 <__x86.get_pc_thunk.dx+0xde>
  100551:	8f                   	(bad)
  100552:	20 48 61             	and    %cl,0x61(%eax)
  100555:	62 69 6c             	bound  %ebp,0x6c(%ecx)
  100558:	69 74 61 72 20 70 61 	imul   $0x67617020,0x72(%ecx,%eiz,2),%esi
  10055f:	67 
  100560:	69 6e 61 c3 a7 c3 a3 	imul   $0xa3c3a7c3,0x61(%esi),%ebp
  100567:	6f                   	outsl  %ds:(%esi),(%dx)
  100568:	0a 00                	or     (%eax),%al
  10056a:	0a 50 61             	or     0x61(%eax),%dl
  10056d:	67 69 6e 61 c3 a7 c3 	imul   $0xa3c3a7c3,0x61(%bp),%ebp
  100574:	a3 
  100575:	6f                   	outsl  %ds:(%esi),(%dx)
  100576:	20 68 61             	and    %ch,0x61(%eax)
  100579:	62 69 6c             	bound  %ebp,0x6c(%ecx)
  10057c:	69 74 61 64 61 0a 00 	imul   $0x30000a61,0x64(%ecx,%eiz,2),%esi
  100583:	30 
  100584:	31 32                	xor    %esi,(%edx)
  100586:	33 34 35 36 37 38 39 	xor    0x39383736(,%esi,1),%esi
  10058d:	61                   	popa
  10058e:	62 63 64             	bound  %esp,0x64(%ebx)
  100591:	65 66 00 0a          	data16 add %cl,%gs:(%edx)
  100595:	50                   	push   %eax
  100596:	61                   	popa
  100597:	67 65 20 66 61       	and    %ah,%gs:0x61(%bp)
  10059c:	75 6c                	jne    10060a <__x86.get_pc_thunk.dx+0x200>
  10059e:	74 0a                	je     1005aa <__x86.get_pc_thunk.dx+0x1a0>
	...

Disassembly of section .note.gnu.property:

001005a4 <.note.gnu.property>:
  1005a4:	04 00                	add    $0x0,%al
  1005a6:	00 00                	add    %al,(%eax)
  1005a8:	18 00                	sbb    %al,(%eax)
  1005aa:	00 00                	add    %al,(%eax)
  1005ac:	05 00 00 00 47       	add    $0x47000000,%eax
  1005b1:	4e                   	dec    %esi
  1005b2:	55                   	push   %ebp
  1005b3:	00 01                	add    %al,(%ecx)
  1005b5:	00 01                	add    %al,(%ecx)
  1005b7:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  1005bb:	00 01                	add    %al,(%ecx)
  1005bd:	00 00                	add    %al,(%eax)
  1005bf:	00 02                	add    %al,(%edx)
  1005c1:	00 01                	add    %al,(%ecx)
  1005c3:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  1005c7:	00 00                	add    %al,(%eax)
  1005c9:	00 00                	add    %al,(%eax)
	...

Disassembly of section .note.gnu.build-id:

001005cc <.note.gnu.build-id>:
  1005cc:	04 00                	add    $0x0,%al
  1005ce:	00 00                	add    %al,(%eax)
  1005d0:	14 00                	adc    $0x0,%al
  1005d2:	00 00                	add    %al,(%eax)
  1005d4:	03 00                	add    (%eax),%eax
  1005d6:	00 00                	add    %al,(%eax)
  1005d8:	47                   	inc    %edi
  1005d9:	4e                   	dec    %esi
  1005da:	55                   	push   %ebp
  1005db:	00 51 3c             	add    %dl,0x3c(%ecx)
  1005de:	c3                   	ret
  1005df:	78 ff                	js     1005e0 <__x86.get_pc_thunk.dx+0x1d6>
  1005e1:	72 e8                	jb     1005cb <__x86.get_pc_thunk.dx+0x1c1>
  1005e3:	db a5 19 fe 34 a3    	(bad) -0x5ccb01e7(%ebp)
  1005e9:	0b 6a dd             	or     -0x23(%edx),%ebp
  1005ec:	db 40 f3             	fildl  -0xd(%eax)
  1005ef:	a3                   	.byte 0xa3

Disassembly of section .eh_frame:

001005f0 <.eh_frame>:
  1005f0:	14 00                	adc    $0x0,%al
  1005f2:	00 00                	add    %al,(%eax)
  1005f4:	00 00                	add    %al,(%eax)
  1005f6:	00 00                	add    %al,(%eax)
  1005f8:	01 7a 52             	add    %edi,0x52(%edx)
  1005fb:	00 01                	add    %al,(%ecx)
  1005fd:	7c 08                	jl     100607 <__x86.get_pc_thunk.dx+0x1fd>
  1005ff:	01 1b                	add    %ebx,(%ebx)
  100601:	0c 04                	or     $0x4,%al
  100603:	04 88                	add    $0x88,%al
  100605:	01 00                	add    %eax,(%eax)
  100607:	00 40 00             	add    %al,0x0(%eax)
  10060a:	00 00                	add    %al,(%eax)
  10060c:	1c 00                	sbb    $0x0,%al
  10060e:	00 00                	add    %al,(%eax)
  100610:	30 fa                	xor    %bh,%dl
  100612:	ff                   	(bad)
  100613:	ff 4b 00             	decl   0x0(%ebx)
  100616:	00 00                	add    %al,(%eax)
  100618:	00 41 0e             	add    %al,0xe(%ecx)
  10061b:	08 87 02 41 0e 0c    	or     %al,0xc0e4102(%edi)
  100621:	86 03                	xchg   %al,(%ebx)
  100623:	41                   	inc    %ecx
  100624:	0e                   	push   %cs
  100625:	10 83 04 43 0e 14    	adc    %al,0x140e4304(%ebx)
  10062b:	6e                   	outsb  %ds:(%esi),(%dx)
  10062c:	0a 0e                	or     (%esi),%cl
  10062e:	10 43 c3             	adc    %al,-0x3d(%ebx)
  100631:	0e                   	push   %cs
  100632:	0c 41                	or     $0x41,%al
  100634:	c6                   	(bad)
  100635:	0e                   	push   %cs
  100636:	08 41 c7             	or     %al,-0x39(%ecx)
  100639:	0e                   	push   %cs
  10063a:	04 47                	add    $0x47,%al
  10063c:	0b 43 0e             	or     0xe(%ebx),%eax
  10063f:	10 43 c3             	adc    %al,-0x3d(%ebx)
  100642:	0e                   	push   %cs
  100643:	0c 43                	or     $0x43,%al
  100645:	c6                   	(bad)
  100646:	0e                   	push   %cs
  100647:	08 41 c7             	or     %al,-0x39(%ecx)
  10064a:	0e                   	push   %cs
  10064b:	04 24                	add    $0x24,%al
  10064d:	00 00                	add    %al,(%eax)
  10064f:	00 60 00             	add    %ah,0x0(%eax)
  100652:	00 00                	add    %al,(%eax)
  100654:	cc                   	int3
  100655:	fc                   	cld
  100656:	ff                   	(bad)
  100657:	ff e2                	jmp    *%edx
  100659:	00 00                	add    %al,(%eax)
  10065b:	00 00                	add    %al,(%eax)
  10065d:	44                   	inc    %esp
  10065e:	0c 01                	or     $0x1,%al
  100660:	00 49 10             	add    %cl,0x10(%ecx)
  100663:	05 02 75 00 41       	add    $0x41007502,%eax
  100668:	10 03                	adc    %al,(%ebx)
  10066a:	02 75 7c             	add    0x7c(%ebp),%dh
  10066d:	4c                   	dec    %esp
  10066e:	0f 03 75 78          	lsl    0x78(%ebp),%esi
  100672:	06                   	push   %es
  100673:	00 10                	add    %dl,(%eax)
  100675:	00 00                	add    %al,(%eax)
  100677:	00 88 00 00 00 86    	add    %cl,-0x7a000000(%eax)
  10067d:	fd                   	std
  10067e:	ff                   	(bad)
  10067f:	ff 04 00             	incl   (%eax,%eax,1)
  100682:	00 00                	add    %al,(%eax)
  100684:	00 00                	add    %al,(%eax)
  100686:	00 00                	add    %al,(%eax)
  100688:	10 00                	adc    %al,(%eax)
  10068a:	00 00                	add    %al,(%eax)
  10068c:	9c                   	pushf
  10068d:	00 00                	add    %al,(%eax)
  10068f:	00 10                	add    %dl,(%eax)
  100691:	fa                   	cli
  100692:	ff                   	(bad)
  100693:	ff 08                	decl   (%eax)
  100695:	00 00                	add    %al,(%eax)
  100697:	00 00                	add    %al,(%eax)
  100699:	00 00                	add    %al,(%eax)
  10069b:	00 10                	add    %dl,(%eax)
  10069d:	00 00                	add    %al,(%eax)
  10069f:	00 b0 00 00 00 0c    	add    %dh,0xc000000(%eax)
  1006a5:	fa                   	cli
  1006a6:	ff                   	(bad)
  1006a7:	ff 08                	decl   (%eax)
  1006a9:	00 00                	add    %al,(%eax)
  1006ab:	00 00                	add    %al,(%eax)
  1006ad:	00 00                	add    %al,(%eax)
  1006af:	00 10                	add    %dl,(%eax)
  1006b1:	00 00                	add    %al,(%eax)
  1006b3:	00 c4                	add    %al,%ah
  1006b5:	00 00                	add    %al,(%eax)
  1006b7:	00 08                	add    %cl,(%eax)
  1006b9:	fa                   	cli
  1006ba:	ff                   	(bad)
  1006bb:	ff 04 00             	incl   (%eax,%eax,1)
  1006be:	00 00                	add    %al,(%eax)
  1006c0:	00 00                	add    %al,(%eax)
  1006c2:	00 00                	add    %al,(%eax)
  1006c4:	10 00                	adc    %al,(%eax)
  1006c6:	00 00                	add    %al,(%eax)
  1006c8:	d8 00                	fadds  (%eax)
  1006ca:	00 00                	add    %al,(%eax)
  1006cc:	04 fa                	add    $0xfa,%al
  1006ce:	ff                   	(bad)
  1006cf:	ff 08                	decl   (%eax)
  1006d1:	00 00                	add    %al,(%eax)
  1006d3:	00 00                	add    %al,(%eax)
  1006d5:	00 00                	add    %al,(%eax)
  1006d7:	00 10                	add    %dl,(%eax)
  1006d9:	00 00                	add    %al,(%eax)
  1006db:	00 ec                	add    %ch,%ah
  1006dd:	00 00                	add    %al,(%eax)
  1006df:	00 00                	add    %al,(%eax)
  1006e1:	fa                   	cli
  1006e2:	ff                   	(bad)
  1006e3:	ff 04 00             	incl   (%eax,%eax,1)
  1006e6:	00 00                	add    %al,(%eax)
  1006e8:	00 00                	add    %al,(%eax)
  1006ea:	00 00                	add    %al,(%eax)
  1006ec:	10 00                	adc    %al,(%eax)
  1006ee:	00 00                	add    %al,(%eax)
  1006f0:	00 01                	add    %al,(%ecx)
  1006f2:	00 00                	add    %al,(%eax)
  1006f4:	fc                   	cld
  1006f5:	f9                   	stc
  1006f6:	ff                   	(bad)
  1006f7:	ff 04 00             	incl   (%eax,%eax,1)
  1006fa:	00 00                	add    %al,(%eax)
  1006fc:	00 00                	add    %al,(%eax)
  1006fe:	00 00                	add    %al,(%eax)
  100700:	10 00                	adc    %al,(%eax)
  100702:	00 00                	add    %al,(%eax)
  100704:	14 01                	adc    $0x1,%al
  100706:	00 00                	add    %al,(%eax)
  100708:	f8                   	clc
  100709:	f9                   	stc
  10070a:	ff                   	(bad)
  10070b:	ff 08                	decl   (%eax)
  10070d:	00 00                	add    %al,(%eax)
  10070f:	00 00                	add    %al,(%eax)
  100711:	00 00                	add    %al,(%eax)
  100713:	00 10                	add    %dl,(%eax)
  100715:	00 00                	add    %al,(%eax)
  100717:	00 28                	add    %ch,(%eax)
  100719:	01 00                	add    %eax,(%eax)
  10071b:	00 f4                	add    %dh,%ah
  10071d:	f9                   	stc
  10071e:	ff                   	(bad)
  10071f:	ff 04 00             	incl   (%eax,%eax,1)
  100722:	00 00                	add    %al,(%eax)
  100724:	00 00                	add    %al,(%eax)
  100726:	00 00                	add    %al,(%eax)
  100728:	10 00                	adc    %al,(%eax)
  10072a:	00 00                	add    %al,(%eax)
  10072c:	3c 01                	cmp    $0x1,%al
  10072e:	00 00                	add    %al,(%eax)
  100730:	f0 f9                	lock stc
  100732:	ff                   	(bad)
  100733:	ff 0c 00             	decl   (%eax,%eax,1)
  100736:	00 00                	add    %al,(%eax)
  100738:	00 00                	add    %al,(%eax)
  10073a:	00 00                	add    %al,(%eax)
  10073c:	10 00                	adc    %al,(%eax)
  10073e:	00 00                	add    %al,(%eax)
  100740:	50                   	push   %eax
  100741:	01 00                	add    %eax,(%eax)
  100743:	00 ec                	add    %ch,%ah
  100745:	f9                   	stc
  100746:	ff                   	(bad)
  100747:	ff 06                	incl   (%esi)
  100749:	00 00                	add    %al,(%eax)
  10074b:	00 00                	add    %al,(%eax)
  10074d:	00 00                	add    %al,(%eax)
  10074f:	00 10                	add    %dl,(%eax)
  100751:	00 00                	add    %al,(%eax)
  100753:	00 64 01 00          	add    %ah,0x0(%ecx,%eax,1)
  100757:	00 e8                	add    %ch,%al
  100759:	f9                   	stc
  10075a:	ff                   	(bad)
  10075b:	ff 1e                	lcall  *(%esi)
  10075d:	00 00                	add    %al,(%eax)
  10075f:	00 00                	add    %al,(%eax)
  100761:	00 00                	add    %al,(%eax)
  100763:	00 28                	add    %ch,(%eax)
  100765:	00 00                	add    %al,(%eax)
  100767:	00 78 01             	add    %bh,0x1(%eax)
  10076a:	00 00                	add    %al,(%eax)
  10076c:	f4                   	hlt
  10076d:	f9                   	stc
  10076e:	ff                   	(bad)
  10076f:	ff 31                	push   (%ecx)
  100771:	00 00                	add    %al,(%eax)
  100773:	00 00                	add    %al,(%eax)
  100775:	41                   	inc    %ecx
  100776:	0e                   	push   %cs
  100777:	08 87 02 41 0e 0c    	or     %al,0xc0e4102(%edi)
  10077d:	86 03                	xchg   %al,(%ebx)
  10077f:	41                   	inc    %ecx
  100780:	0e                   	push   %cs
  100781:	10 83 04 6b c3 0e    	adc    %al,0xec36b04(%ebx)
  100787:	0c 41                	or     $0x41,%al
  100789:	c6                   	(bad)
  10078a:	0e                   	push   %cs
  10078b:	08 41 c7             	or     %al,-0x39(%ecx)
  10078e:	0e                   	push   %cs
  10078f:	04 44                	add    $0x44,%al
  100791:	00 00                	add    %al,(%eax)
  100793:	00 a4 01 00 00 08 fa 	add    %ah,-0x5f80000(%ecx,%eax,1)
  10079a:	ff                   	(bad)
  10079b:	ff f4                	push   %esp
  10079d:	00 00                	add    %al,(%eax)
  10079f:	00 00                	add    %al,(%eax)
  1007a1:	4c                   	dec    %esp
  1007a2:	0e                   	push   %cs
  1007a3:	08 87 02 41 0e 0c    	or     %al,0xc0e4102(%edi)
  1007a9:	86 03                	xchg   %al,(%ebx)
  1007ab:	41                   	inc    %ecx
  1007ac:	0e                   	push   %cs
  1007ad:	10 83 04 43 0e 20    	adc    %al,0x200e4304(%ebx)
  1007b3:	02 b1 0a 0e 10 41    	add    0x41100e0a(%ecx),%dh
  1007b9:	c3                   	ret
  1007ba:	0e                   	push   %cs
  1007bb:	0c 41                	or     $0x41,%al
  1007bd:	c6                   	(bad)
  1007be:	0e                   	push   %cs
  1007bf:	08 41 c7             	or     %al,-0x39(%ecx)
  1007c2:	0e                   	push   %cs
  1007c3:	04 41                	add    $0x41,%al
  1007c5:	0b 5d 0a             	or     0xa(%ebp),%ebx
  1007c8:	0e                   	push   %cs
  1007c9:	10 41 c3             	adc    %al,-0x3d(%ecx)
  1007cc:	0e                   	push   %cs
  1007cd:	0c 41                	or     $0x41,%al
  1007cf:	c6                   	(bad)
  1007d0:	0e                   	push   %cs
  1007d1:	08 41 c7             	or     %al,-0x39(%ecx)
  1007d4:	0e                   	push   %cs
  1007d5:	04 41                	add    $0x41,%al
  1007d7:	0b 24 00             	or     (%eax,%eax,1),%esp
  1007da:	00 00                	add    %al,(%eax)
  1007dc:	ec                   	in     (%dx),%al
  1007dd:	01 00                	add    %eax,(%eax)
  1007df:	00 c0                	add    %al,%al
  1007e1:	fa                   	cli
  1007e2:	ff                   	(bad)
  1007e3:	ff                   	(bad)
  1007e4:	3e 00 00             	add    %al,%ds:(%eax)
  1007e7:	00 00                	add    %al,(%eax)
  1007e9:	4b                   	dec    %ebx
  1007ea:	0e                   	push   %cs
  1007eb:	08 85 02 41 0e 0c    	or     %al,0xc0e4102(%ebp)
  1007f1:	87 03                	xchg   %eax,(%ebx)
  1007f3:	41                   	inc    %ecx
  1007f4:	0e                   	push   %cs
  1007f5:	10 86 04 46 0e 14    	adc    %al,0x140e4604(%esi)
  1007fb:	83 05 00 00 00 10 00 	addl   $0x0,0x10000000
  100802:	00 00                	add    %al,(%eax)
  100804:	14 02                	adc    $0x2,%al
  100806:	00 00                	add    %al,(%eax)
  100808:	d8 fa                	fdivr  %st(2),%st
  10080a:	ff                   	(bad)
  10080b:	ff 33                	push   (%ebx)
  10080d:	00 00                	add    %al,(%eax)
  10080f:	00 00                	add    %al,(%eax)
  100811:	00 00                	add    %al,(%eax)
  100813:	00 10                	add    %dl,(%eax)
  100815:	00 00                	add    %al,(%eax)
  100817:	00 28                	add    %ch,(%eax)
  100819:	02 00                	add    (%eax),%al
  10081b:	00 ea                	add    %ch,%dl
  10081d:	fb                   	sti
  10081e:	ff                   	(bad)
  10081f:	ff 04 00             	incl   (%eax,%eax,1)
  100822:	00 00                	add    %al,(%eax)
  100824:	00 00                	add    %al,(%eax)
  100826:	00 00                	add    %al,(%eax)
  100828:	10 00                	adc    %al,(%eax)
  10082a:	00 00                	add    %al,(%eax)
  10082c:	3c 02                	cmp    $0x2,%al
  10082e:	00 00                	add    %al,(%eax)
  100830:	da fb                	(bad)
  100832:	ff                   	(bad)
  100833:	ff 04 00             	incl   (%eax,%eax,1)
  100836:	00 00                	add    %al,(%eax)
  100838:	00 00                	add    %al,(%eax)
	...

Disassembly of section .eh_frame_hdr:

0010083c <__GNU_EH_FRAME_HDR>:
  10083c:	01 1b                	add    %ebx,(%ebx)
  10083e:	03 3b                	add    (%ebx),%edi
  100840:	b0 fd                	mov    $0xfd,%al
  100842:	ff                   	(bad)
  100843:	ff 14 00             	call   *(%eax,%eax,1)
  100846:	00 00                	add    %al,(%eax)
  100848:	04 f8                	add    $0xf8,%al
  10084a:	ff                   	(bad)
  10084b:	ff cc                	dec    %esp
  10084d:	fd                   	std
  10084e:	ff                   	(bad)
  10084f:	ff 64 f8 ff          	jmp    *-0x1(%eax,%edi,8)
  100853:	ff 4c fe ff          	decl   -0x1(%esi,%edi,8)
  100857:	ff 74 f8 ff          	push   -0x1(%eax,%edi,8)
  10085b:	ff 60 fe             	jmp    *-0x2(%eax)
  10085e:	ff                   	(bad)
  10085f:	ff 84 f8 ff ff 74 fe 	incl   -0x18b0001(%eax,%edi,8)
  100866:	ff                   	(bad)
  100867:	ff 94 f8 ff ff 88 fe 	call   *-0x1770001(%eax,%edi,8)
  10086e:	ff                   	(bad)
  10086f:	ff a4 f8 ff ff 9c fe 	jmp    *-0x1630001(%eax,%edi,8)
  100876:	ff                   	(bad)
  100877:	ff b4 f8 ff ff b0 fe 	push   -0x14f0001(%eax,%edi,8)
  10087e:	ff                   	(bad)
  10087f:	ff c4                	inc    %esp
  100881:	f8                   	clc
  100882:	ff                   	(bad)
  100883:	ff c4                	inc    %esp
  100885:	fe                   	(bad)
  100886:	ff                   	(bad)
  100887:	ff d4                	call   *%esp
  100889:	f8                   	clc
  10088a:	ff                   	(bad)
  10088b:	ff                   	lcall  (bad)
  10088c:	d8 fe                	fdivr  %st(6),%st
  10088e:	ff                   	(bad)
  10088f:	ff e4                	jmp    *%esp
  100891:	f8                   	clc
  100892:	ff                   	(bad)
  100893:	ff                   	ljmp   (bad)
  100894:	ec                   	in     (%dx),%al
  100895:	fe                   	(bad)
  100896:	ff                   	(bad)
  100897:	ff f4                	push   %esp
  100899:	f8                   	clc
  10089a:	ff                   	(bad)
  10089b:	ff 00                	incl   (%eax)
  10089d:	ff                   	(bad)
  10089e:	ff                   	(bad)
  10089f:	ff 04 f9             	incl   (%ecx,%edi,8)
  1008a2:	ff                   	(bad)
  1008a3:	ff 14 ff             	call   *(%edi,%edi,8)
  1008a6:	ff                   	(bad)
  1008a7:	ff 24 f9             	jmp    *(%ecx,%edi,8)
  1008aa:	ff                   	(bad)
  1008ab:	ff 28                	ljmp   *(%eax)
  1008ad:	ff                   	(bad)
  1008ae:	ff                   	(bad)
  1008af:	ff 64 f9 ff          	jmp    *-0x1(%ecx,%edi,8)
  1008b3:	ff 54 ff ff          	call   *-0x1(%edi,%edi,8)
  1008b7:	ff 64 fa ff          	jmp    *-0x1(%edx,%edi,8)
  1008bb:	ff 9c ff ff ff a4 fa 	lcall  *-0x55b0001(%edi,%edi,8)
  1008c2:	ff                   	(bad)
  1008c3:	ff c4                	inc    %esp
  1008c5:	ff                   	(bad)
  1008c6:	ff                   	(bad)
  1008c7:	ff e4                	jmp    *%esp
  1008c9:	fa                   	cli
  1008ca:	ff                   	(bad)
  1008cb:	ff 10                	call   *(%eax)
  1008cd:	fe                   	(bad)
  1008ce:	ff                   	(bad)
  1008cf:	ff c6                	inc    %esi
  1008d1:	fb                   	sti
  1008d2:	ff                   	(bad)
  1008d3:	ff                   	(bad)
  1008d4:	38 fe                	cmp    %bh,%dh
  1008d6:	ff                   	(bad)
  1008d7:	ff ca                	dec    %edx
  1008d9:	fb                   	sti
  1008da:	ff                   	(bad)
  1008db:	ff                   	lcall  (bad)
  1008dc:	d8 ff                	fdivr  %st(7),%st
  1008de:	ff                   	(bad)
  1008df:	ff ce                	dec    %esi
  1008e1:	fb                   	sti
  1008e2:	ff                   	(bad)
  1008e3:	ff                   	ljmp   (bad)
  1008e4:	ec                   	in     (%dx),%al
  1008e5:	ff                   	(bad)
  1008e6:	ff                   	(bad)
  1008e7:	ff                   	.byte 0xff

Disassembly of section .data:

001008e8 <desc.0>:
  1008e8:	77 00                	ja     1008ea <desc.0+0x2>
  1008ea:	00 20                	add    %ah,(%eax)
  1008ec:	11 00                	adc    %eax,(%eax)

Disassembly of section .got.plt:

001008f0 <_GLOBAL_OFFSET_TABLE_>:
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	47                   	inc    %edi
   1:	43                   	inc    %ebx
   2:	43                   	inc    %ebx
   3:	3a 20                	cmp    (%eax),%ah
   5:	28 47 4e             	sub    %al,0x4e(%edi)
   8:	55                   	push   %ebp
   9:	29 20                	sub    %esp,(%eax)
   b:	31 35 2e 31 2e 31    	xor    %esi,0x312e312e
  11:	20 32                	and    %dh,(%edx)
  13:	30 32                	xor    %dh,(%edx)
  15:	35 30 34 32 35       	xor    $0x35323430,%eax
	...
