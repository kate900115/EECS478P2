#include "circuit.h"

int Circuit::createADDModule(const string &input1, const string &input2, const string &cin, const string &output, const string &cout, unsigned int numBits)
{
  Node* node;
  // create input1 and input2 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create cin node
  node = createNode(cin);
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create cout
  node = createNode(cout);
  
  // create internal nodes C
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"c" ;
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create other internal nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"d" ;
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"e" ;
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"f" ;
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"g" ;
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
  	Node* internal_c_previous;
    if(i!=0)
    {
    	stringstream sstr;
    	sstr << i-1;
    	string name = output+"c";
    	name = name + "[" + sstr.str() + "]";
    	internal_c_previous = findNode(name);
    	assert(internal_c_previous != NULL);
    }
  
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    name = input1 + "[" + sstr.str() + "]";
    Node* inNode1 = findNode(name);
    assert(inNode1 != NULL);
    
    name = input2 + "[" + sstr.str() + "]";
    Node* inNode2 = findNode(name);
    assert(inNode2 != NULL);
    
    //internal node for c(n-1) to c0
    name = output+"c";
    name = name + "[" + sstr.str() + "]";
    Node* internal_c = findNode(name);
    assert(internal_c != NULL);
    
    //internal node1
    name = output+"d";
    name = name + "[" + sstr.str() + "]";
    Node* dd = findNode(name);
    assert(dd != NULL);
    
    //internal node2
    name = output+"e";
    name = name + "[" + sstr.str() + "]";
    Node* ee = findNode(name);
    assert(ee != NULL);
    
    //internal node3
    name = output+"f";
    name = name + "[" + sstr.str() + "]";
    Node* ff = findNode(name);
    assert(ff != NULL);
    
    //internal node4
    name = output+"g";
    name = name + "[" + sstr.str() + "]";
    Node* gg = findNode(name);
    assert(gg != NULL);

    Node* c_in = findNode(cin);
    assert(c_in != NULL);
    Node* c_out = findNode(cout);
    assert(c_out != NULL);
    
    
    
    
    if (i==0)
    {
    		//s0=a0^b0^cin;
    		createXOR3Node(inNode1, inNode2, c_in, outNode);
    		
    		//c0=a0*b0+b0*cin+cin*a0;
    		createAND2Node(inNode1,inNode2,dd);
    		createAND2Node(inNode1,c_in,ee);
    		createAND2Node(inNode2,c_in,ff);
    		createOR2Node(dd,ee,gg);
    		createOR2Node(gg,ff,internal_c);
    }
    else if ( i==(numBits-1) )
    {
    		//sn=an^bn^c(n-1);
    		createXOR3Node(inNode1, inNode2, internal_c_previous, outNode);
    		
    		//cn=an*bn+bn*c(n-1)+c(n-1)*an;
    		createAND2Node(inNode1,inNode2,dd);
    		createAND2Node(inNode1,internal_c_previous,ee);
    		createAND2Node(inNode2,internal_c_previous,ff);
    		createOR2Node(dd,ee,gg);
    		createOR2Node(gg,ff,c_out);
    }
    else
    {
    		//sk=ak^bk^c(k-1);
    		createXOR3Node(inNode1, inNode2, internal_c_previous, outNode);
    		
    		//ck=ak*bk+bk*c(k-1)+c(k-1)*ak;
    		createAND2Node(inNode1,inNode2,dd);
    		createAND2Node(inNode1,internal_c_previous,ee);
    		createAND2Node(inNode2,internal_c_previous,ff);
    		createOR2Node(dd,ee,gg);
    		createOR2Node(gg,ff,internal_c);
    }
  }
  
  // when you have implemented this function,
  // change 'return -1' to 'return 0'
  return 0;
}

int Circuit::createSUBModule(const string &input1, const string &input2, const string &output, unsigned int numBits)
{
  Node* node;
  // create input nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input1 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input2 + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create one node and zero node
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  Node* oneNode = createNode("ONE");
  createONENode(oneNode);
  
  // create c_out node
  Node* c_out = createNode("cout");
  
  // create internal1 nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output+"h";
    name = name + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // inverse the input2
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output +"h";
    name = name + "[" + sstr.str() + "]";
    Node* hh = findNode(name);
    assert(hh != NULL);
    
    name = input2 + "[" + sstr.str() + "]";
    Node* inNode2 = findNode(name);
    assert(inNode2 != NULL);
    
    createXOR3Node(zeroNode, oneNode, inNode2, hh);
  }
  
  // add input1 and the complemented input2
  createADDModule(input1, output+"h", "ONE", output, "cout" ,numBits);
  
  // when you have implemented this function,
  // change 'return -1' to 'return 0'
  return 0;
}


int Circuit::createSHIFTModule(const string &input, const string &output, unsigned int numBits, unsigned int numShift)
{
  Node* node;
  // create input nodes
  for (unsigned int i = 0; i < numBits; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = input + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // create output nodes
  for (unsigned int i = 0; i < numBits+numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    node = createNode(name);
  }
  
  // assign '0's to the least numShift bits
  Node* zeroNode = createNode("ZERO");
  createZERONode(zeroNode);
  
  for (unsigned int i = 0; i < numShift; ++i)
  {
    stringstream sstr;
    sstr << i;
    string name = output + "[" + sstr.str() + "]";
    
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    createBUF1Node(zeroNode, outNode);
  }
  
  // assign inputs to the remaining numBits bits
  for (unsigned int i = numShift; i < numBits+numShift; ++i)
  {
    string name;
    
    // find input node[i-numShift]
    stringstream inStr;
    inStr << i-numShift;
    name = input + "[" + inStr.str() + "]";
    Node* inNode = findNode(name);
    assert(inNode != NULL);
    
    // find output node[i]
    stringstream outStr;
    outStr << i;
    name = output + "[" + outStr.str() + "]";
    Node* outNode = findNode(name);
    assert(outNode != NULL);
    
    // assign
    createBUF1Node(inNode, outNode);
  }
  
  return 0;
}

