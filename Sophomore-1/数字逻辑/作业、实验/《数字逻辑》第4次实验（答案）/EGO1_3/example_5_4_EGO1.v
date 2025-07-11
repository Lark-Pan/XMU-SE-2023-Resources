//�ṹ��������ʽ����ģ�������Ϊ������ʽ��ʵ������5.4��3λ����������λ�Ĵ���������x��CPΪ������������ߵĲ��������Լ�S1������״̬��y3��y2��y1�������ZΪ������������ߵ�3��LED���Լ����ұߵ�LED�ơ�

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

module t_flip_flop(
    input t,                               	  
    input cp,                                                         
    output q, qn		
);
    reg y;
    always @(negedge cp)                     //��Ϊ������ʽ
    begin
                case(t)
	               0: y <= y;			      //  T  =  0       Y=����
	               1: y <= ~y;		      //  T  =  1       Y=~Y
                endcase
    end
    assign  q= y;
    assign qn = ~y;
endmodule

module example_5_4(
    input cp, x,                               		 
    input y3, y2, y1,				
    output ny3, ny2, ny1, z    		 	        
);
    wire t1, t2, t3, t4;
    wire ny3n, ny2n, ny1n;

    xor_gate U1(.a(x),.b(y1),.f(t1));				//�ṹ��������ʽ
    xor_gate U2(.a(y1),.b(y2),.f(t2));				//�ṹ��������ʽ
    xor_gate U3(.a(y2),.b(y3),.f(t3));				//�ṹ��������ʽ

    xor_gate U4(.a(y2),.b(y3),.f(t4));				//�ṹ��������ʽ
    xor_gate U5(.a(t4),.b(y1),.f(z));				//�ṹ��������ʽ

    t_flip_flop U6(.t(t3),.cp(cp),.q(ny3),.qn(ny3n));			//�ṹ��������ʽ
    t_flip_flop U7(.t(t2),.cp(cp),.q(ny2),.qn(ny2n));			//�ṹ��������ʽ
    t_flip_flop U8(.t(t1),.cp(cp),.q(ny1),.qn(ny1n));			//�ṹ��������ʽ

endmodule

module example_5_4_exe(
    input sw_pin[7:0],                               		 //8����������
    input btn_1,				 //1����ť
    output [15:0] led_pin    		 	//16��led��            
);
    reg y3, y2, y1;

    example_5_4 U(.cp(btn_1), .x(sw_pin[0]), .y3(y3), .y2(y2), .y1(y1), .ny3(led_pin[0]), .ny2(led_pin[1]), .ny1(led_pin[2]), .z(led_pin[7]));

    initial begin
        y3=0;
        y2=0;
        y1=0;
    end

    always @(*)                     		//��Ϊ������ʽ
    begin
	y3 <= led_pin[0];
	y2 <= led_pin[1];
	y1 <= led_pin[2];
    end

endmodule