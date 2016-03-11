#include "circuit.h"

int Circuit::createABSMIN5X3YModule(const string &input1, const string &input2, const string &output)
{
	int input_length = 16;
	int output_length = 19; 
	
	Node* node;
  	
  	// create zero node, one node
  	Node* zeroNode = createNode("ZERO");
  	createZERONode(zeroNode);
  	
  	Node* oneNode = createNode("ONE");
  	createONENode(oneNode);

	//create 19_bits_zero_node
    for (unsigned int i = 0; i < output_length; ++i)
    {
    	stringstream sstr;
    	sstr << i;
    	string name = "19_zero" ;
    	name = name + "[" + sstr.str() + "]";
    
    	node = createNode(name);
    	createZERONode(node);
  	}
  	
  	// to calculate x_4 = input1 x 4
  	createSHIFTModule(input1, "x_4", input_length, 2);
  	
  	// to add two more bits to input so it can be 18 bits.
  	string name = input1 + "[15]";
  	Node* input1_15 = findNode(name);
    assert(input1_15 != NULL);
    
   	name = input1 + "[16]";
   	Node* input1_16 = createNode(name);
   	
   	name = input1 + "[17]";
   	Node* input1_17 = createNode(name);
   	
   	// for debug
   	//name = input1 + "[18]";
   	//Node* input1_18 = createNode(name);
   	
	createBUF1Node(input1_15, input1_16);
	createBUF1Node(input1_15, input1_17);
  	
  	// for debug
  	//Node* Node_x4_18 = createNode("x_4[18]");
  	//createZERONode(Node_x4_18);
  	
  	// to calculate x_5 = input1 x 5
  	createADDModule(input1, "x_4", "ZERO", "x_5", "x_5[18]", 18);
  	
  	// to calculate y_2 = input2 x 2
  	createSHIFTModule(input2, "y_2", input_length, 1);
  	
  	// to add one more bits to input2 so it can be 17 bits.
  	name = input2 + "[15]";
  	Node* input2_15 = findNode(name);
    assert(input2_15 != NULL);
    
   	name = input2 + "[16]";
   	Node* input2_16 = createNode(name);
   	
   	createBUF1Node(input2_15, input2_16);
   
  	// to calculate y_3 = input2 x 3  	
  	createADDModule(input2, "y_2", "ZERO", "y_3", "y_3[17]", 17);

  	// create y_3[18], so y_3 can be 19 bits
  	Node* sign_of_y3 = findNode("y_3[17]");
  	assert(sign_of_y3 != NULL);
  	Node* y3_18 = createNode("y_3[18]");
  	
  	createBUF1Node(sign_of_y3, y3_18);
  	
  	// to calculate x5_y3 = input1 x 5 - input2 x 3
  	createSUBModule("x_5", "y_3", "x5_y3", output_length);
  	
  	// use the highest bit to figure out whether it is negative or positive 

	Node* sign_of_x5_y3 = findNode("x5_y3[18]");
	assert(sign_of_x5_y3 != NULL);
    
	Node* sign_of_x5 = findNode("x_5[18]");
	assert(sign_of_x5 != NULL);
	
	// to calculate the select signal s1
	Node* s2 = createNode("s2");
	createOR2Node(sign_of_x5, sign_of_y3, s2);
	
	// to calculate the select signal s2
	Node* t1 = createNode("t1");
	Node* t2 = createNode("t2");
	Node* t3 = createNode("t3");
	Node* t4 = createNode("t4");
	Node* t5 = createNode("t5");
	Node* t6 = createNode("t6");
	Node* s1 = createNode("s1");
	
	createXOR3Node(zeroNode, oneNode, sign_of_x5_y3 , t1);
	createXOR3Node(zeroNode, oneNode, sign_of_x5 , t2);
	createAND2Node(t1, t2, t3);
	createAND2Node(t1, sign_of_y3, t4);
	createAND2Node(t2, sign_of_y3, t5);
	createOR2Node(t3, t4, t6);
	createOR2Node(t6, t5, s1);
	
	// to calculate the for input of MUX 4
	createSUBModule("19_zero", "x_5", "neg_x5", output_length);	
	createSUBModule("x_5", "19_zero", "pos_x5", output_length);
	createSUBModule("19_zero", "y_3", "neg_y3", output_length);	
	createSUBModule("y_3", "19_zero", "pos_y3", output_length);
	
	/*for (unsigned int i = 0; i < output_length; ++i)
	{
		stringstream sstr;
    	sstr << i;
    	string name = "neg_y3";
    	name = name + "[" + sstr.str() + "]";
    	Node* Node_x5 = findNode(name);
    	name = output + "[" + sstr.str() + "]";
    	Node* outNode = createNode(name);
    	createBUF1Node(Node_x5, outNode);
    	
	}*/
	
	// build up the MUX for output
	for (unsigned int i = 0; i < output_length; ++i)
	{
		stringstream sstr;
    	sstr << i;

    	string name = "neg_x5";
    	name = name + "[" + sstr.str() + "]";    	
    	Node* Node_neg_x5 = findNode(name);
    	
    	name = "pos_x5";
    	name = name + "[" + sstr.str() + "]";    	
    	Node* Node_pos_x5 = findNode(name);
    	
    	name = "neg_y3";
    	name = name + "[" + sstr.str() + "]";    	
    	Node* Node_neg_y3 = findNode(name);
    	
    	name = "pos_y3";
    	name = name + "[" + sstr.str() + "]";  
    	Node* Node_pos_y3 = findNode(name);
    	
    	name = output + "[" + sstr.str() + "]";
    	Node* outNode = createNode(name);
    	
		createMUX4Node(s1, s2,  Node_pos_x5,  Node_pos_y3,  Node_neg_x5,  Node_neg_y3, outNode);
	}
	
  	
  // after you have implemented this function,
  // change 'return -1' to 'return 0'
  return 0;
}
