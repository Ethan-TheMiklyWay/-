#int pof2[6] ={ 1��2��8��4��16��10 } ���ҵ����ֵ������¼��
.data
array: .space 24

.text
main:
#���Ƚ�������ĸ�ֵ
la $t0,array #��array�ĵ�ַװ��t0�Ĵ�����         t0
li $t1,1     #��1װ��t1�Ĵ�����ʱ����              t1
sw $t1,($t0) #��t1�Ĵ�����ֵ���뵽array��ַ��
li $t1,2
sw $t1,4($t0)
li $t1,8
sw $t1,8($t0)
li $t1,4
sw $t1,12($t0)
li $t1,16
sw $t1,16($t0)
li $t1,10
sw $t1,20($t0)

li $t5,6 #i=6                                   t5
li $t6,1#j=1                                    t6
li $t9,-10# t9��ʾ������¼�����ֵmax value     t9
while:    #while(true)
sub $t5,$t5,$t6 #i=i-j=i-1
sll $t4,$t5,2 #address offset = i*4             t4
add $t7,$t4,$t0 #��ƫ�����ӻ���ַ�ҵ���Ӧ�ĵ�ַ t7
lw $t8,($t7)  #����Ӧ�ĵ�ַ����װ�뵽t8��       t8

slt $t3,$t9,$t8   #��t8�õ�������t9 max�Ƚϣ�     t3
#if ($9 < $8) $3=1; else $3=0���������t3��
beq $t3,$zero,done #����ȽϽ��Ϊ0��Ҳ����s9>s7��
#���ֵmax�Ѿ���s7����ֱ��������ֵ
move $t9,$t8
done:

beq $t5,$zero,finish #if(i==0) goto finish
beq $zero,$zero,while #else goto while

finish:    #while ����
li  $v0,1
move  $a0,$t9
syscall
#������洢��t9��a0�Ĵ�����

