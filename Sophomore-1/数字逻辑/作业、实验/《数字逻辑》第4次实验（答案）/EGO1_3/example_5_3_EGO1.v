//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������5.3�Ĵ��мӷ������õ�·������Ϊx1��x2��״̬Ϊy�����ΪZ��CPΪʱ���źš�

`timescale 1ns / 1ps	

module xor_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= a ^ b; 
    end
    assign f = y;
endmodule

module nand_gate(
    input a,
    input b,
    output f                               
);
    reg y;
    always @(*)                        //��Ϊ������ʽ
    begin
        y <= ~(a & b); 
    end
    assign f = y;
endmodule

module d_flip_flop(
    input d,                               	  
    input cp,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //��Ϊ������ʽ
    begin
                case(d)
	               0: y <= 0;			      //  D  =  01       Y=0
	               1: y <= 1;			      //  D  =  10       Y=1
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_3(
    input cp, x1, x2,                               		 
    input y,				
    output ny, z    		 	        
);

    wire t1, t2, t3, d, nyn;

    xor_gate U1(.a(x1),.b(x2),.f(t1));				//�ṹ��������ʽ
    nand_gate U2(.a(t1),.b(y),.f(t2));				//�ṹ��������ʽ
    nand_gate U3(.a(x1),.b(x2),.f(t3));				//�ṹ��������ʽ
    nand_gate U4(.a(t2),.b(t3),.f(d));				//�ṹ��������ʽ
    xor_gate U5(.a(t1),.b(y),.f(z));				//�ṹ��������ʽ
    d_flip_flop U6(.d(d),.cp(cp),.q(ny),.qn(nyn));			//�ṹ��������ʽ

endmodule