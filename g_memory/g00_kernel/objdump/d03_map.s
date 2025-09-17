
./build/k03_map:     file format elf32-i386


Disassembly of section .text:

00100000 <multiboot_header>:
  100000:	02 b0 ad 1b 00 00    	add    0x1bad(%eax),%dh
  100006:	00 00                	add    %al,(%eax)
  100008:	fe 4f 52             	decb   0x52(%edi)
  10000b:	e4                 	in     $0xbc,%al

0010000c <start>:
  10000c:	bc 00 10 11 00       	mov    $0x111000,%esp
  100011:	e9 aa 02 00 00       	jmp    1002c0 <main>

00100016 <page_fault_entry>:
  100016:	60                   	pusha
  100017:	54                   	push   %esp
  100018:	e8 23 02 00 00       	call   100240 <page_fault_handler>
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

00100040 <invlpg>:
  100040:	8b 44 24 04          	mov    0x4(%esp),%eax
  100044:	0f 01 38             	invlpg (%eax)
  100047:	c3                   	ret
  100048:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10004f:	00 

00100050 <set_cr4>:
  100050:	8b 44 24 04          	mov    0x4(%esp),%eax
  100054:	0f 22 e0             	mov    %eax,%cr4
  100057:	c3                   	ret
  100058:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10005f:	00 

00100060 <get_cr4>:
  100060:	0f 20 e0             	mov    %cr4,%eax
  100063:	c3                   	ret
  100064:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10006b:	00 
  10006c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100070 <set_cr3>:
  100070:	8b 44 24 04          	mov    0x4(%esp),%eax
  100074:	0f 22 d8             	mov    %eax,%cr3
  100077:	c3                   	ret
  100078:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10007f:	00 

00100080 <get_cr3>:
  100080:	0f 20 d8             	mov    %cr3,%eax
  100083:	c3                   	ret
  100084:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10008b:	00 
  10008c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100090 <get_cr2>:
  100090:	0f 20 d0             	mov    %cr2,%eax
  100093:	c3                   	ret
  100094:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10009b:	00 
  10009c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001000a0 <set_cr0>:
  1000a0:	8b 44 24 04          	mov    0x4(%esp),%eax
  1000a4:	0f 22 c0             	mov    %eax,%cr0
  1000a7:	c3                   	ret
  1000a8:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000af:	00 

001000b0 <get_cr0>:
  1000b0:	0f 20 c0             	mov    %cr0,%eax
  1000b3:	c3                   	ret
  1000b4:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000bb:	00 
  1000bc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001000c0 <outb>:
  1000c0:	0f b6 44 24 04       	movzbl 0x4(%esp),%eax
  1000c5:	0f b7 54 24 08       	movzwl 0x8(%esp),%edx
  1000ca:	ee                   	out    %al,(%dx)
  1000cb:	c3                   	ret
  1000cc:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

001000d0 <inb>:
  1000d0:	8b 54 24 04          	mov    0x4(%esp),%edx
  1000d4:	ec                   	in     (%dx),%al
  1000d5:	c3                   	ret
  1000d6:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1000dd:	00 
  1000de:	66 90                	xchg   %ax,%ax

001000e0 <putc>:
  1000e0:	0f b6 4c 24 04       	movzbl 0x4(%esp),%ecx
  1000e5:	ba fd 03 00 00       	mov    $0x3fd,%edx
  1000ea:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
  1000f0:	ec                   	in     (%dx),%al
  1000f1:	a8 20                	test   $0x20,%al
  1000f3:	74 fb                	je     1000f0 <putc+0x10>
  1000f5:	ba f8 03 00 00       	mov    $0x3f8,%edx
  1000fa:	89 c8                	mov    %ecx,%eax
  1000fc:	ee                   	out    %al,(%dx)
  1000fd:	c3                   	ret
  1000fe:	66 90                	xchg   %ax,%ax

00100100 <puts>:
  100100:	57                   	push   %edi
  100101:	56                   	push   %esi
  100102:	53                   	push   %ebx
  100103:	8b 74 24 10          	mov    0x10(%esp),%esi
  100107:	0f b6 1e             	movzbl (%esi),%ebx
  10010a:	84 db                	test   %bl,%bl
  10010c:	74 1f                	je     10012d <puts+0x2d>
  10010e:	66 90                	xchg   %ax,%ax
  100110:	ba fd 03 00 00       	mov    $0x3fd,%edx
  100115:	ec                   	in     (%dx),%al
  100116:	a8 20                	test   $0x20,%al
  100118:	74 f6                	je     100110 <puts+0x10>
  10011a:	89 d8                	mov    %ebx,%eax
  10011c:	ba f8 03 00 00       	mov    $0x3f8,%edx
  100121:	ee                   	out    %al,(%dx)
  100122:	0f b6 5e 01          	movzbl 0x1(%esi),%ebx
  100126:	83 c6 01             	add    $0x1,%esi
  100129:	84 db                	test   %bl,%bl
  10012b:	75 e3                	jne    100110 <puts+0x10>
  10012d:	5b                   	pop    %ebx
  10012e:	5e                   	pop    %esi
  10012f:	5f                   	pop    %edi
  100130:	c3                   	ret
  100131:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  100138:	00 
  100139:	8d b4 26 00 00 00 00 	lea    0x0(%esi,%eiz,1),%esi

00100140 <put_hex>:
  100140:	e8 bb 01 00 00       	call   100300 <__x86.get_pc_thunk.dx>
  100145:	81 c2 f7 04 00 00    	add    $0x4f7,%edx
  10014b:	57                   	push   %edi
  10014c:	56                   	push   %esi
  10014d:	53                   	push   %ebx
  10014e:	83 ec 10             	sub    $0x10,%esp
  100151:	8b 44 24 20          	mov    0x20(%esp),%eax
  100155:	c6 44 24 0f 00       	movb   $0x0,0xf(%esp)
  10015a:	85 c0                	test   %eax,%eax
  10015c:	0f 84 c5 00 00 00    	je     100227 <put_hex+0xe7>
  100162:	8d 5c 24 0e          	lea    0xe(%esp),%ebx
  100166:	8d ba d6 fc ff ff    	lea    -0x32a(%edx),%edi
  10016c:	89 d9                	mov    %ebx,%ecx
  10016e:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  100175:	00 
  100176:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10017d:	00 
  10017e:	66 90                	xchg   %ax,%ax
  100180:	89 c2                	mov    %eax,%edx
  100182:	83 e9 01             	sub    $0x1,%ecx
  100185:	83 e2 0f             	and    $0xf,%edx
  100188:	0f b6 34 17          	movzbl (%edi,%edx,1),%esi
  10018c:	89 f2                	mov    %esi,%edx
  10018e:	88 51 01             	mov    %dl,0x1(%ecx)
  100191:	c1 e8 04             	shr    $0x4,%eax
  100194:	75 ea                	jne    100180 <put_hex+0x40>
  100196:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10019b:	2e 8d 74 26 00       	lea    %cs:0x0(%esi,%eiz,1),%esi
  1001a0:	ec                   	in     (%dx),%al
  1001a1:	a8 20                	test   $0x20,%al
  1001a3:	74 fb                	je     1001a0 <put_hex+0x60>
  1001a5:	b8 30 00 00 00       	mov    $0x30,%eax
  1001aa:	ba f8 03 00 00       	mov    $0x3f8,%edx
  1001af:	ee                   	out    %al,(%dx)
  1001b0:	ba fd 03 00 00       	mov    $0x3fd,%edx
  1001b5:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  1001bc:	00 
  1001bd:	8d 76 00             	lea    0x0(%esi),%esi
  1001c0:	ec                   	in     (%dx),%al
  1001c1:	a8 20                	test   $0x20,%al
  1001c3:	74 fb                	je     1001c0 <put_hex+0x80>
  1001c5:	b8 78 00 00 00       	mov    $0x78,%eax
  1001ca:	ba f8 03 00 00       	mov    $0x3f8,%edx
  1001cf:	ee                   	out    %al,(%dx)
  1001d0:	39 d9                	cmp    %ebx,%ecx
  1001d2:	74 32                	je     100206 <put_hex+0xc6>
  1001d4:	89 f0                	mov    %esi,%eax
  1001d6:	84 c0                	test   %al,%al
  1001d8:	74 25                	je     1001ff <put_hex+0xbf>
  1001da:	8d 59 01             	lea    0x1(%ecx),%ebx
  1001dd:	8d 76 00             	lea    0x0(%esi),%esi
  1001e0:	ba fd 03 00 00       	mov    $0x3fd,%edx
  1001e5:	ec                   	in     (%dx),%al
  1001e6:	a8 20                	test   $0x20,%al
  1001e8:	74 f6                	je     1001e0 <put_hex+0xa0>
  1001ea:	89 f0                	mov    %esi,%eax
  1001ec:	ba f8 03 00 00       	mov    $0x3f8,%edx
  1001f1:	ee                   	out    %al,(%dx)
  1001f2:	0f b6 73 01          	movzbl 0x1(%ebx),%esi
  1001f6:	83 c3 01             	add    $0x1,%ebx
  1001f9:	89 f0                	mov    %esi,%eax
  1001fb:	84 c0                	test   %al,%al
  1001fd:	75 e1                	jne    1001e0 <put_hex+0xa0>
  1001ff:	83 c4 10             	add    $0x10,%esp
  100202:	5b                   	pop    %ebx
  100203:	5e                   	pop    %esi
  100204:	5f                   	pop    %edi
  100205:	c3                   	ret
  100206:	ba fd 03 00 00       	mov    $0x3fd,%edx
  10020b:	2e 8d 74 26 00       	lea    %cs:0x0(%esi,%eiz,1),%esi
  100210:	ec                   	in     (%dx),%al
  100211:	a8 20                	test   $0x20,%al
  100213:	74 fb                	je     100210 <put_hex+0xd0>
  100215:	b8 30 00 00 00       	mov    $0x30,%eax
  10021a:	ba f8 03 00 00       	mov    $0x3f8,%edx
  10021f:	ee                   	out    %al,(%dx)
  100220:	83 c4 10             	add    $0x10,%esp
  100223:	5b                   	pop    %ebx
  100224:	5e                   	pop    %esi
  100225:	5f                   	pop    %edi
  100226:	c3                   	ret
  100227:	8d 5c 24 0e          	lea    0xe(%esp),%ebx
  10022b:	31 f6                	xor    %esi,%esi
  10022d:	89 d9                	mov    %ebx,%ecx
  10022f:	e9 62 ff ff ff       	jmp    100196 <put_hex+0x56>
  100234:	2e 8d b4 26 00 00 00 	lea    %cs:0x0(%esi,%eiz,1),%esi
  10023b:	00 
  10023c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

00100240 <page_fault_handler>:
  100240:	e8 b7 00 00 00       	call   1002fc <__x86.get_pc_thunk.ax>
  100245:	05 f7 03 00 00       	add    $0x3f7,%eax
  10024a:	55                   	push   %ebp
  10024b:	57                   	push   %edi
  10024c:	56                   	push   %esi
  10024d:	be 0a 00 00 00       	mov    $0xa,%esi
  100252:	53                   	push   %ebx
  100253:	8d a8 f3 fc ff ff    	lea    -0x30d(%eax),%ebp
  100259:	8d 98 e7 fc ff ff    	lea    -0x319(%eax),%ebx
  10025f:	90                   	nop
  100260:	ba fd 03 00 00       	mov    $0x3fd,%edx
  100265:	ec                   	in     (%dx),%al
  100266:	a8 20                	test   $0x20,%al
  100268:	74 f6                	je     100260 <page_fault_handler+0x20>
  10026a:	89 f0                	mov    %esi,%eax
  10026c:	ba f8 03 00 00       	mov    $0x3f8,%edx
  100271:	ee                   	out    %al,(%dx)
  100272:	83 c3 01             	add    $0x1,%ebx
  100275:	0f b6 33             	movzbl (%ebx),%esi
  100278:	39 eb                	cmp    %ebp,%ebx
  10027a:	75 e4                	jne    100260 <page_fault_handler+0x20>
  10027c:	eb fe                	jmp    10027c <page_fault_handler+0x3c>
  10027e:	66 90                	xchg   %ax,%ax

00100280 <init_idt>:
  100280:	e8 77 00 00 00       	call   1002fc <__x86.get_pc_thunk.ax>
  100285:	05 b7 03 00 00       	add    $0x3b7,%eax
  10028a:	c7 80 36 0a 01 00 08 	movl   $0x8f000008,0x10a36(%eax)
  100291:	00 00 8f 
  100294:	c7 c2 16 00 10 00    	mov    $0x100016,%edx
  10029a:	66 89 90 34 0a 01 00 	mov    %dx,0x10a34(%eax)
  1002a1:	c1 ea 10             	shr    $0x10,%edx
  1002a4:	66 89 90 3a 0a 01 00 	mov    %dx,0x10a3a(%eax)
  1002ab:	0f 01 98 f8 ff ff ff 	lidtl  -0x8(%eax)
  1002b2:	c3                   	ret
  1002b3:	66 90                	xchg   %ax,%ax
  1002b5:	66 90                	xchg   %ax,%ax
  1002b7:	66 90                	xchg   %ax,%ax
  1002b9:	66 90                	xchg   %ax,%ax
  1002bb:	66 90                	xchg   %ax,%ax
  1002bd:	66 90                	xchg   %ax,%ax
  1002bf:	90                   	nop

001002c0 <main>:
  1002c0:	8d 4c 24 04          	lea    0x4(%esp),%ecx
  1002c4:	83 e4 f0             	and    $0xfffffff0,%esp
  1002c7:	ff 71 fc             	push   -0x4(%ecx)
  1002ca:	55                   	push   %ebp
  1002cb:	89 e5                	mov    %esp,%ebp
  1002cd:	53                   	push   %ebx
  1002ce:	e8 25 00 00 00       	call   1002f8 <__x86.get_pc_thunk.bx>
  1002d3:	81 c3 69 03 00 00    	add    $0x369,%ebx
  1002d9:	51                   	push   %ecx
  1002da:	83 ec 0c             	sub    $0xc,%esp
  1002dd:	8d 83 c8 fc ff ff    	lea    -0x338(%ebx),%eax
  1002e3:	50                   	push   %eax
  1002e4:	e8 17 fe ff ff       	call   100100 <puts>
  1002e9:	83 c4 10             	add    $0x10,%esp
  1002ec:	8d 65 f8             	lea    -0x8(%ebp),%esp
  1002ef:	31 c0                	xor    %eax,%eax
  1002f1:	59                   	pop    %ecx
  1002f2:	5b                   	pop    %ebx
  1002f3:	5d                   	pop    %ebp
  1002f4:	8d 61 fc             	lea    -0x4(%ecx),%esp
  1002f7:	c3                   	ret

001002f8 <__x86.get_pc_thunk.bx>:
  1002f8:	8b 1c 24             	mov    (%esp),%ebx
  1002fb:	c3                   	ret

001002fc <__x86.get_pc_thunk.ax>:
  1002fc:	8b 04 24             	mov    (%esp),%eax
  1002ff:	c3                   	ret

00100300 <__x86.get_pc_thunk.dx>:
  100300:	8b 14 24             	mov    (%esp),%edx
  100303:	c3                   	ret

Disassembly of section .rodata:

00100304 <.rodata>:
  100304:	0a 4f 6c             	or     0x6c(%edi),%cl
  100307:	c3                   	ret
  100308:	a1 20 6d 75 6e       	mov    0x6e756d20,%eax
  10030d:	64 6f                	outsl  %fs:(%esi),(%dx)
  10030f:	21 0a                	and    %ecx,(%edx)
  100311:	00 30                	add    %dh,(%eax)
  100313:	31 32                	xor    %esi,(%edx)
  100315:	33 34 35 36 37 38 39 	xor    0x39383736(,%esi,1),%esi
  10031c:	61                   	popa
  10031d:	62 63 64             	bound  %esp,0x64(%ebx)
  100320:	65 66 00 0a          	data16 add %cl,%gs:(%edx)
  100324:	50                   	push   %eax
  100325:	61                   	popa
  100326:	67 65 20 66 61       	and    %ah,%gs:0x61(%bp)
  10032b:	75 6c                	jne    100399 <__x86.get_pc_thunk.dx+0x99>
  10032d:	74 0a                	je     100339 <__x86.get_pc_thunk.dx+0x39>
	...

Disassembly of section .note.gnu.property:

00100330 <.note.gnu.property>:
  100330:	04 00                	add    $0x0,%al
  100332:	00 00                	add    %al,(%eax)
  100334:	18 00                	sbb    %al,(%eax)
  100336:	00 00                	add    %al,(%eax)
  100338:	05 00 00 00 47       	add    $0x47000000,%eax
  10033d:	4e                   	dec    %esi
  10033e:	55                   	push   %ebp
  10033f:	00 01                	add    %al,(%ecx)
  100341:	00 01                	add    %al,(%ecx)
  100343:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  100347:	00 01                	add    %al,(%ecx)
  100349:	00 00                	add    %al,(%eax)
  10034b:	00 02                	add    %al,(%edx)
  10034d:	00 01                	add    %al,(%ecx)
  10034f:	c0 04 00 00          	rolb   $0x0,(%eax,%eax,1)
  100353:	00 00                	add    %al,(%eax)
  100355:	00 00                	add    %al,(%eax)
	...

Disassembly of section .note.gnu.build-id:

00100358 <.note.gnu.build-id>:
  100358:	04 00                	add    $0x0,%al
  10035a:	00 00                	add    %al,(%eax)
  10035c:	14 00                	adc    $0x0,%al
  10035e:	00 00                	add    %al,(%eax)
  100360:	03 00                	add    (%eax),%eax
  100362:	00 00                	add    %al,(%eax)
  100364:	47                   	inc    %edi
  100365:	4e                   	dec    %esi
  100366:	55                   	push   %ebp
  100367:	00 fa                	add    %bh,%dl
  100369:	cc                   	int3
  10036a:	fd                   	std
  10036b:	e6 6c                	out    %al,$0x6c
  10036d:	eb b1                	jmp    100320 <__x86.get_pc_thunk.dx+0x20>
  10036f:	c0 fb de             	sar    $0xde,%bl
  100372:	a3 2b 73 7f fe       	mov    %eax,0xfe7f732b
  100377:	4c                   	dec    %esp
  100378:	0c be                	or     $0xbe,%al
  10037a:	0c a1                	or     $0xa1,%al

Disassembly of section .eh_frame:

0010037c <.eh_frame>:
  10037c:	14 00                	adc    $0x0,%al
  10037e:	00 00                	add    %al,(%eax)
  100380:	00 00                	add    %al,(%eax)
  100382:	00 00                	add    %al,(%eax)
  100384:	01 7a 52             	add    %edi,0x52(%edx)
  100387:	00 01                	add    %al,(%ecx)
  100389:	7c 08                	jl     100393 <__x86.get_pc_thunk.dx+0x93>
  10038b:	01 1b                	add    %ebx,(%ebx)
  10038d:	0c 04                	or     $0x4,%al
  10038f:	04 88                	add    $0x88,%al
  100391:	01 00                	add    %eax,(%eax)
  100393:	00 30                	add    %dh,(%eax)
  100395:	00 00                	add    %al,(%eax)
  100397:	00 1c 00             	add    %bl,(%eax,%eax,1)
  10039a:	00 00                	add    %al,(%eax)
  10039c:	24 ff                	and    $0xff,%al
  10039e:	ff                   	(bad)
  10039f:	ff                   	(bad)
  1003a0:	38 00                	cmp    %al,(%eax)
  1003a2:	00 00                	add    %al,(%eax)
  1003a4:	00 44 0c 01          	add    %al,0x1(%esp,%ecx,1)
  1003a8:	00 49 10             	add    %cl,0x10(%ecx)
  1003ab:	05 02 75 00 41       	add    $0x41007502,%eax
  1003b0:	10 03                	adc    %al,(%ebx)
  1003b2:	02 75 7c             	add    0x7c(%ebp),%dh
  1003b5:	4c                   	dec    %esp
  1003b6:	0f 03 75 78          	lsl    0x78(%ebp),%esi
  1003ba:	06                   	push   %es
  1003bb:	58                   	pop    %eax
  1003bc:	c1 0c 01 00          	rorl   $0x0,(%ecx,%eax,1)
  1003c0:	41                   	inc    %ecx
  1003c1:	c3                   	ret
  1003c2:	41                   	inc    %ecx
  1003c3:	c5 43 0c             	lds    0xc(%ebx),%eax
  1003c6:	04 04                	add    $0x4,%al
  1003c8:	10 00                	adc    %al,(%eax)
  1003ca:	00 00                	add    %al,(%eax)
  1003cc:	50                   	push   %eax
  1003cd:	00 00                	add    %al,(%eax)
  1003cf:	00 28                	add    %ch,(%eax)
  1003d1:	ff                   	(bad)
  1003d2:	ff                   	(bad)
  1003d3:	ff 04 00             	incl   (%eax,%eax,1)
  1003d6:	00 00                	add    %al,(%eax)
  1003d8:	00 00                	add    %al,(%eax)
  1003da:	00 00                	add    %al,(%eax)
  1003dc:	10 00                	adc    %al,(%eax)
  1003de:	00 00                	add    %al,(%eax)
  1003e0:	64 00 00             	add    %al,%fs:(%eax)
  1003e3:	00 5c fc ff          	add    %bl,-0x1(%esp,%edi,8)
  1003e7:	ff 08                	decl   (%eax)
  1003e9:	00 00                	add    %al,(%eax)
  1003eb:	00 00                	add    %al,(%eax)
  1003ed:	00 00                	add    %al,(%eax)
  1003ef:	00 10                	add    %dl,(%eax)
  1003f1:	00 00                	add    %al,(%eax)
  1003f3:	00 78 00             	add    %bh,0x0(%eax)
  1003f6:	00 00                	add    %al,(%eax)
  1003f8:	58                   	pop    %eax
  1003f9:	fc                   	cld
  1003fa:	ff                   	(bad)
  1003fb:	ff 08                	decl   (%eax)
  1003fd:	00 00                	add    %al,(%eax)
  1003ff:	00 00                	add    %al,(%eax)
  100401:	00 00                	add    %al,(%eax)
  100403:	00 10                	add    %dl,(%eax)
  100405:	00 00                	add    %al,(%eax)
  100407:	00 8c 00 00 00 54 fc 	add    %cl,-0x3ac0000(%eax,%eax,1)
  10040e:	ff                   	(bad)
  10040f:	ff 04 00             	incl   (%eax,%eax,1)
  100412:	00 00                	add    %al,(%eax)
  100414:	00 00                	add    %al,(%eax)
  100416:	00 00                	add    %al,(%eax)
  100418:	10 00                	adc    %al,(%eax)
  10041a:	00 00                	add    %al,(%eax)
  10041c:	a0 00 00 00 50       	mov    0x50000000,%al
  100421:	fc                   	cld
  100422:	ff                   	(bad)
  100423:	ff 08                	decl   (%eax)
  100425:	00 00                	add    %al,(%eax)
  100427:	00 00                	add    %al,(%eax)
  100429:	00 00                	add    %al,(%eax)
  10042b:	00 10                	add    %dl,(%eax)
  10042d:	00 00                	add    %al,(%eax)
  10042f:	00 b4 00 00 00 4c fc 	add    %dh,-0x3b40000(%eax,%eax,1)
  100436:	ff                   	(bad)
  100437:	ff 04 00             	incl   (%eax,%eax,1)
  10043a:	00 00                	add    %al,(%eax)
  10043c:	00 00                	add    %al,(%eax)
  10043e:	00 00                	add    %al,(%eax)
  100440:	10 00                	adc    %al,(%eax)
  100442:	00 00                	add    %al,(%eax)
  100444:	c8 00 00 00          	enter  $0x0,$0x0
  100448:	48                   	dec    %eax
  100449:	fc                   	cld
  10044a:	ff                   	(bad)
  10044b:	ff 04 00             	incl   (%eax,%eax,1)
  10044e:	00 00                	add    %al,(%eax)
  100450:	00 00                	add    %al,(%eax)
  100452:	00 00                	add    %al,(%eax)
  100454:	10 00                	adc    %al,(%eax)
  100456:	00 00                	add    %al,(%eax)
  100458:	dc 00                	faddl  (%eax)
  10045a:	00 00                	add    %al,(%eax)
  10045c:	44                   	inc    %esp
  10045d:	fc                   	cld
  10045e:	ff                   	(bad)
  10045f:	ff 08                	decl   (%eax)
  100461:	00 00                	add    %al,(%eax)
  100463:	00 00                	add    %al,(%eax)
  100465:	00 00                	add    %al,(%eax)
  100467:	00 10                	add    %dl,(%eax)
  100469:	00 00                	add    %al,(%eax)
  10046b:	00 f0                	add    %dh,%al
  10046d:	00 00                	add    %al,(%eax)
  10046f:	00 40 fc             	add    %al,-0x4(%eax)
  100472:	ff                   	(bad)
  100473:	ff 04 00             	incl   (%eax,%eax,1)
  100476:	00 00                	add    %al,(%eax)
  100478:	00 00                	add    %al,(%eax)
  10047a:	00 00                	add    %al,(%eax)
  10047c:	10 00                	adc    %al,(%eax)
  10047e:	00 00                	add    %al,(%eax)
  100480:	04 01                	add    $0x1,%al
  100482:	00 00                	add    %al,(%eax)
  100484:	3c fc                	cmp    $0xfc,%al
  100486:	ff                   	(bad)
  100487:	ff 0c 00             	decl   (%eax,%eax,1)
  10048a:	00 00                	add    %al,(%eax)
  10048c:	00 00                	add    %al,(%eax)
  10048e:	00 00                	add    %al,(%eax)
  100490:	10 00                	adc    %al,(%eax)
  100492:	00 00                	add    %al,(%eax)
  100494:	18 01                	sbb    %al,(%ecx)
  100496:	00 00                	add    %al,(%eax)
  100498:	38 fc                	cmp    %bh,%ah
  10049a:	ff                   	(bad)
  10049b:	ff 06                	incl   (%esi)
  10049d:	00 00                	add    %al,(%eax)
  10049f:	00 00                	add    %al,(%eax)
  1004a1:	00 00                	add    %al,(%eax)
  1004a3:	00 10                	add    %dl,(%eax)
  1004a5:	00 00                	add    %al,(%eax)
  1004a7:	00 2c 01             	add    %ch,(%ecx,%eax,1)
  1004aa:	00 00                	add    %al,(%eax)
  1004ac:	34 fc                	xor    $0xfc,%al
  1004ae:	ff                   	(bad)
  1004af:	ff 1e                	lcall  *(%esi)
  1004b1:	00 00                	add    %al,(%eax)
  1004b3:	00 00                	add    %al,(%eax)
  1004b5:	00 00                	add    %al,(%eax)
  1004b7:	00 28                	add    %ch,(%eax)
  1004b9:	00 00                	add    %al,(%eax)
  1004bb:	00 40 01             	add    %al,0x1(%eax)
  1004be:	00 00                	add    %al,(%eax)
  1004c0:	40                   	inc    %eax
  1004c1:	fc                   	cld
  1004c2:	ff                   	(bad)
  1004c3:	ff 31                	push   (%ecx)
  1004c5:	00 00                	add    %al,(%eax)
  1004c7:	00 00                	add    %al,(%eax)
  1004c9:	41                   	inc    %ecx
  1004ca:	0e                   	push   %cs
  1004cb:	08 87 02 41 0e 0c    	or     %al,0xc0e4102(%edi)
  1004d1:	86 03                	xchg   %al,(%ebx)
  1004d3:	41                   	inc    %ecx
  1004d4:	0e                   	push   %cs
  1004d5:	10 83 04 6b c3 0e    	adc    %al,0xec36b04(%ebx)
  1004db:	0c 41                	or     $0x41,%al
  1004dd:	c6                   	(bad)
  1004de:	0e                   	push   %cs
  1004df:	08 41 c7             	or     %al,-0x39(%ecx)
  1004e2:	0e                   	push   %cs
  1004e3:	04 44                	add    $0x44,%al
  1004e5:	00 00                	add    %al,(%eax)
  1004e7:	00 6c 01 00          	add    %ch,0x0(%ecx,%eax,1)
  1004eb:	00 54 fc ff          	add    %dl,-0x1(%esp,%edi,8)
  1004ef:	ff f4                	push   %esp
  1004f1:	00 00                	add    %al,(%eax)
  1004f3:	00 00                	add    %al,(%eax)
  1004f5:	4c                   	dec    %esp
  1004f6:	0e                   	push   %cs
  1004f7:	08 87 02 41 0e 0c    	or     %al,0xc0e4102(%edi)
  1004fd:	86 03                	xchg   %al,(%ebx)
  1004ff:	41                   	inc    %ecx
  100500:	0e                   	push   %cs
  100501:	10 83 04 43 0e 20    	adc    %al,0x200e4304(%ebx)
  100507:	02 b1 0a 0e 10 41    	add    0x41100e0a(%ecx),%dh
  10050d:	c3                   	ret
  10050e:	0e                   	push   %cs
  10050f:	0c 41                	or     $0x41,%al
  100511:	c6                   	(bad)
  100512:	0e                   	push   %cs
  100513:	08 41 c7             	or     %al,-0x39(%ecx)
  100516:	0e                   	push   %cs
  100517:	04 41                	add    $0x41,%al
  100519:	0b 5d 0a             	or     0xa(%ebp),%ebx
  10051c:	0e                   	push   %cs
  10051d:	10 41 c3             	adc    %al,-0x3d(%ecx)
  100520:	0e                   	push   %cs
  100521:	0c 41                	or     $0x41,%al
  100523:	c6                   	(bad)
  100524:	0e                   	push   %cs
  100525:	08 41 c7             	or     %al,-0x39(%ecx)
  100528:	0e                   	push   %cs
  100529:	04 41                	add    $0x41,%al
  10052b:	0b 24 00             	or     (%eax,%eax,1),%esp
  10052e:	00 00                	add    %al,(%eax)
  100530:	b4 01                	mov    $0x1,%ah
  100532:	00 00                	add    %al,(%eax)
  100534:	0c fd                	or     $0xfd,%al
  100536:	ff                   	(bad)
  100537:	ff                   	(bad)
  100538:	3e 00 00             	add    %al,%ds:(%eax)
  10053b:	00 00                	add    %al,(%eax)
  10053d:	4b                   	dec    %ebx
  10053e:	0e                   	push   %cs
  10053f:	08 85 02 41 0e 0c    	or     %al,0xc0e4102(%ebp)
  100545:	87 03                	xchg   %eax,(%ebx)
  100547:	41                   	inc    %ecx
  100548:	0e                   	push   %cs
  100549:	10 86 04 46 0e 14    	adc    %al,0x140e4604(%esi)
  10054f:	83 05 00 00 00 10 00 	addl   $0x0,0x10000000
  100556:	00 00                	add    %al,(%eax)
  100558:	dc 01                	faddl  (%ecx)
  10055a:	00 00                	add    %al,(%eax)
  10055c:	24 fd                	and    $0xfd,%al
  10055e:	ff                   	(bad)
  10055f:	ff 33                	push   (%ebx)
  100561:	00 00                	add    %al,(%eax)
  100563:	00 00                	add    %al,(%eax)
  100565:	00 00                	add    %al,(%eax)
  100567:	00 10                	add    %dl,(%eax)
  100569:	00 00                	add    %al,(%eax)
  10056b:	00 f0                	add    %dh,%al
  10056d:	01 00                	add    %eax,(%eax)
  10056f:	00 8c fd ff ff 04 00 	add    %cl,0x4ffff(%ebp,%edi,8)
  100576:	00 00                	add    %al,(%eax)
  100578:	00 00                	add    %al,(%eax)
  10057a:	00 00                	add    %al,(%eax)
  10057c:	10 00                	adc    %al,(%eax)
  10057e:	00 00                	add    %al,(%eax)
  100580:	04 02                	add    $0x2,%al
  100582:	00 00                	add    %al,(%eax)
  100584:	7c fd                	jl     100583 <__x86.get_pc_thunk.dx+0x283>
  100586:	ff                   	(bad)
  100587:	ff 04 00             	incl   (%eax,%eax,1)
  10058a:	00 00                	add    %al,(%eax)
  10058c:	00 00                	add    %al,(%eax)
	...

Disassembly of section .eh_frame_hdr:

00100590 <__GNU_EH_FRAME_HDR>:
  100590:	01 1b                	add    %ebx,(%ebx)
  100592:	03 3b                	add    (%ebx),%edi
  100594:	e8 fd ff ff 13       	call   14100596 <idt.1+0x13fef596>
  100599:	00 00                	add    %al,(%eax)
  10059b:	00 b0 fa ff ff 4c    	add    %dh,0x4cfffffa(%eax)
  1005a1:	fe                   	(bad)
  1005a2:	ff                   	(bad)
  1005a3:	ff c0                	inc    %eax
  1005a5:	fa                   	cli
  1005a6:	ff                   	(bad)
  1005a7:	ff 60 fe             	jmp    *-0x2(%eax)
  1005aa:	ff                   	(bad)
  1005ab:	ff d0                	call   *%eax
  1005ad:	fa                   	cli
  1005ae:	ff                   	(bad)
  1005af:	ff 74 fe ff          	push   -0x1(%esi,%edi,8)
  1005b3:	ff e0                	jmp    *%eax
  1005b5:	fa                   	cli
  1005b6:	ff                   	(bad)
  1005b7:	ff 88 fe ff ff f0    	decl   -0xf000002(%eax)
  1005bd:	fa                   	cli
  1005be:	ff                   	(bad)
  1005bf:	ff 9c fe ff ff 00 fb 	lcall  *-0x4ff0001(%esi,%edi,8)
  1005c6:	ff                   	(bad)
  1005c7:	ff b0 fe ff ff 10    	push   0x10fffffe(%eax)
  1005cd:	fb                   	sti
  1005ce:	ff                   	(bad)
  1005cf:	ff c4                	inc    %esp
  1005d1:	fe                   	(bad)
  1005d2:	ff                   	(bad)
  1005d3:	ff 20                	jmp    *(%eax)
  1005d5:	fb                   	sti
  1005d6:	ff                   	(bad)
  1005d7:	ff                   	lcall  (bad)
  1005d8:	d8 fe                	fdivr  %st(6),%st
  1005da:	ff                   	(bad)
  1005db:	ff 30                	push   (%eax)
  1005dd:	fb                   	sti
  1005de:	ff                   	(bad)
  1005df:	ff                   	ljmp   (bad)
  1005e0:	ec                   	in     (%dx),%al
  1005e1:	fe                   	(bad)
  1005e2:	ff                   	(bad)
  1005e3:	ff 40 fb             	incl   -0x5(%eax)
  1005e6:	ff                   	(bad)
  1005e7:	ff 00                	incl   (%eax)
  1005e9:	ff                   	(bad)
  1005ea:	ff                   	(bad)
  1005eb:	ff 50 fb             	call   *-0x5(%eax)
  1005ee:	ff                   	(bad)
  1005ef:	ff 14 ff             	call   *(%edi,%edi,8)
  1005f2:	ff                   	(bad)
  1005f3:	ff 70 fb             	push   -0x5(%eax)
  1005f6:	ff                   	(bad)
  1005f7:	ff 28                	ljmp   *(%eax)
  1005f9:	ff                   	(bad)
  1005fa:	ff                   	(bad)
  1005fb:	ff b0 fb ff ff 54    	push   0x54fffffb(%eax)
  100601:	ff                   	(bad)
  100602:	ff                   	(bad)
  100603:	ff b0 fc ff ff 9c    	push   -0x63000004(%eax)
  100609:	ff                   	(bad)
  10060a:	ff                   	(bad)
  10060b:	ff f0                	push   %eax
  10060d:	fc                   	cld
  10060e:	ff                   	(bad)
  10060f:	ff c4                	inc    %esp
  100611:	ff                   	(bad)
  100612:	ff                   	(bad)
  100613:	ff 30                	push   (%eax)
  100615:	fd                   	std
  100616:	ff                   	(bad)
  100617:	ff 04 fe             	incl   (%esi,%edi,8)
  10061a:	ff                   	(bad)
  10061b:	ff 68 fd             	ljmp   *-0x3(%eax)
  10061e:	ff                   	(bad)
  10061f:	ff                   	(bad)
  100620:	38 fe                	cmp    %bh,%dh
  100622:	ff                   	(bad)
  100623:	ff 6c fd ff          	ljmp   *-0x1(%ebp,%edi,8)
  100627:	ff                   	lcall  (bad)
  100628:	d8 ff                	fdivr  %st(7),%st
  10062a:	ff                   	(bad)
  10062b:	ff 70 fd             	push   -0x3(%eax)
  10062e:	ff                   	(bad)
  10062f:	ff                   	ljmp   (bad)
  100630:	ec                   	in     (%dx),%al
  100631:	ff                   	(bad)
  100632:	ff                   	(bad)
  100633:	ff                   	.byte 0xff

Disassembly of section .data:

00100634 <desc.0>:
  100634:	77 00                	ja     100636 <desc.0+0x2>
  100636:	00 10                	add    %dl,(%eax)
  100638:	11 00                	adc    %eax,(%eax)

Disassembly of section .got.plt:

0010063c <_GLOBAL_OFFSET_TABLE_>:
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
