#include <stdio.h>
#include <header/CommandLine.h>
#include <header/Open_File.h>
#include <header/Table.h>
#include <header/Text.h>
#include <header/Error.h>
#include <header/String_Input.h>
#include <header/Tree.h>
#include <header/Code.h>
#include <header/CodeGenerator.h>  
#define LeftMode 0
#define RightMode 1

    /*  ABSTRACT MACHINE OPERATIONS  */
#define    NOP          1   /* 'NOP'       */
#define    HALTOP       2   /* 'HALT'      */      
#define    LITOP        3   /* 'LIT'       */
#define    LLVOP        4   /* 'LLV'       */
#define    LGVOP        5   /* 'LGV'       */
#define    SLVOP        6   /* 'SLV'       */
#define    SGVOP        7   /* 'SGV'       */
#define    LLAOP        8   /* 'LLA'       */
#define    LGAOP        9   /* 'LGA'       */
#define    UOPOP       10   /* 'UOP'       */
#define    BOPOP       11   /* 'BOP'       */     
#define    POPOP       12   /* 'POP'       */  
#define    DUPOP       13   /* 'DUP'       */
#define    SWAPOP      14   /* 'SWAP'      */
#define    CALLOP      15   /* 'CALL'      */
#define    RTNOP       16   /* 'RTN'       */
#define    GOTOOP      17   /* 'GOTO'      */
#define    CONDOP      18   /* 'COND'      */
#define    CODEOP      19   /* 'CODE'      */
#define    SOSOP       20   /* 'SOS'       */
#define    LIMITOP     21   /* 'LIMIT'     */

    /* ABSTRACT MACHINE OPERANDS */

         /* UNARY OPERANDS */
#define    UNOT        22   /* 'UNOT'     */
#define    UNEG        23   /* 'UNEG'     */
#define    USUCC       24   /* 'USUCC'    */
#define    UPRED       25   /* 'UPRED'    */
         /* BINARY OPERANDS */
#define    BAND        26   /* 'BAND'     */
#define    BOR         27   /* 'BOR'      */
#define    BPLUS       28   /* 'BPLUS'    */
#define    BMINUS      29   /* 'BMINUS'   */
#define    BMULT       30   /* 'BMULT'    */
#define    BDIV        31   /* 'BDIV'     */
#define    BEXP        32   /* 'BEXP'     */
#define    BMOD        33   /* 'BMOD'     */
#define    BEQ         34   /* 'BEQ'      */
#define    BNE         35   /* 'BNE'      */
#define    BLE         36   /* 'BLE'      */
#define    BGE         37   /* 'BGE'      */
#define    BLT         38   /* 'BLT'      */
#define    BGT         39   /* 'BGT'      */
         /* OS SERVICE CALL OPERANDS */
#define    TRACEX      40   /* 'TRACEX'   */
#define    DUMPMEM     41   /* 'DUMPMEM'  */
#define    OSINPUT     42   /* 'INPUT'    */
#define    OSINPUTC    43   /* 'INPUT'    */
#define    OSOUTPUT    44   /* 'OUTPUT'   */
#define    OSOUTPUTC   45   /* 'OUTPUT'   */
#define    OSOUTPUTL   46   /* 'OUTPUTL'  */
#define    OSEOF       47   /* 'EOF'      */

         /* TREE NODE NAMES */
#define    ProgramNode  48   /* 'program'  */
#define    TypesNode    49   /* 'types'    */
#define    TypeNode     50   /* 'type'     */
#define    DclnsNode    51   /* 'dclns'    */
#define    VarNode      52   /* 'var'     */
#define    IntegerTNode 53   /* 'integer'  */
#define    BooleanTNode 54   /* 'boolean'  */
#define    BlockNode    55   /* 'block'    */
#define    AssignNode   56   /* 'assign'   */
#define    OutputNode   57   /* 'output'   */ 
#define    IfNode       58   /* 'if'       */
#define    WhileNode    59   /* 'while'    */
#define    NullNode     60   /* '<null>'   */
#define    LENode       61   /* '<='       */
#define    PlusNode     62   /* '+'        */
#define    MinusNode    63   /* '-'        */
#define    ReadNode     64   /* 'read'     */
#define    IntegerNode  65   /* '<integer>'*/
#define    IdentifierNode 66 /* '<identifier>'*/
#define    EofNode      67   /* 'eof'      */
#define    BooleanNodeTrue  68   /* '<boolean_true>' */ 
#define    BooleanNodeFalse 69   /* '<boolean_false>'*/
#define    EQNode       70   /*  '='       */   
#define    NENode       71   /*  '<>'      */
#define    GENode       72   /*  '>='      */
#define    LTNode       73   /*  '<'       */
#define    GTNode       74   /*  '>'       */
#define    NotNode      75   /*  'not'     */
#define    ModNode      76   /*  'mod'     */
#define    AndNode      77   /*  'and'     */
#define    OrNode       78   /*  'or'      */
#define    MulNode      79   /*  '*'       */ 
#define    PowerNode    80   /*  '**'      */
#define    DivideNode   81   /*  '/'       */ 
#define    SwapNode     82   /*  'swap'    */        
#define    RepeatNode   83   /*  'repeat'  */
#define    LoopNode     84   /*  'loop'    */
#define    ExitNode     85   /*  'exit'    */
#define    UptoNode     86   /*  'upto'    */
#define    DowntoNode   87   /*  'downto'  */
#define    CaseNode     88   /*  'case'    */
#define    CaseClauseNode 89 /*  'case_clause' */
#define    OtherwiseNode  90 /*  'otherwise'*/ 
#define    RangeClauseNode 91 /* 'range'       */
#define    CharTNode     92  /*  'char'     */
#define    CharNode      93  /*  '<char>'   */
#define    ConstsNode    94  /*  'consts'   */
#define    ConstNode     95  /*  'const'    */
#define    LitNode       96  /*  'lit'      */
#define    SuccNode      97  /*  'succ'     */
#define    PredNode      98  /*  'pred'     */
#define    OrdNode       99  /*  'ord'      */
#define    ChrNode       100 /*  'chr'      */
#define    OutputTypeNode 101 /* 'type_disambiguation' */
#define    StringNode    102 /*  '<string>' */
#define    StringTNode   103 /*  'string'   */
#define    CallNode      104 /*  'call'     */
#define    FcnNode       105 /*  'function' */
#define    ProcedureNode 106 /*  'procedure' */
#define    SubprogsNode  107 /*  'subprogs'  */
#define    ParamsNode    108 /*  'params'    */
#define    ReturnNode    109 /*  'return'    */
 
#define    NumberOfNodes 109 /* '<identifier>'*/
typedef int Mode;

FILE *CodeFile;
char *CodeFileName;
Clabel HaltLabel;

char *mach_op[] = 
    {"NOP","HALT","LIT","LLV","LGV","SLV","SGV","LLA","LGA",
     "UOP","BOP","POP","DUP","SWAP","CALL","RTN","GOTO","COND",
     "CODE","SOS","LIMIT","UNOT","UNEG","USUCC","UPRED","BAND",
     "BOR","BPLUS","BMINUS","BMULT","BDIV","BEXP","BMOD","BEQ",
     "BNE","BLE","BGE","BLT","BGT","TRACEX","DUMPMEM","INPUT",
     "INPUTC","OUTPUT","OUTPUTC","OUTPUTL","EOF"};

/****************************************************************** 
   add new node names to the end of the array, keeping in strict order
   as defined above, then adjust the j loop control variable in
   InitializeNodeNames(). 
*******************************************************************/
char *node_name[] =
    {"program","types","type","dclns","var","integer",
     "boolean","block","assign","output","if","while",
     "<null>","<=","+","-","read","<integer>","<identifier>","eof","true",
     "false", "=", "<>", ">=", "<", ">"
     , "not", "mod", "and", "or", "*", "exp", "/", "swap", "repeat",
     "loop", "exit", "upto", "downto", "case", "case_clause", "otherwise", "range",
     "char", "<char>", "consts", "const", "lit", "succ", "pred", "ord", "chr",
     "type_disambiguation", "<string>", "string", "call", "function", "procedure", "subprogs", "params", "return"};



void CodeGenerate(int argc, char *argv[])
{
   int NumberTrees;

   InitializeCodeGenerator(argc,argv);
   Tree_File = Open_File("_TREE", "r"); 
   NumberTrees = Read_Trees();
   fclose (Tree_File);                     

   HaltLabel = ProcessNode (RootOfTree(1), NoLabel);
   CodeGen0 (HALTOP, HaltLabel); 

   CodeFile = Open_File (CodeFileName, "w");
   DumpCode (CodeFile);
   fclose(CodeFile); 

   if (TraceSpecified)
      fclose (TraceFile);

/****************************************************************** 
  enable this code to write out the tree after the code generator
  has run.  It will show the new decorations made with MakeAddress().
*******************************************************************/


   Tree_File = fopen("_TREE", "w");  
   Write_Trees();
   fclose (Tree_File);                   
}


void InitializeCodeGenerator(int argc,char *argv[])
{
   InitializeMachineOperations();
   InitializeNodeNames();
   FrameSize = 0;
   CurrentProcLevel = 0;
   LabelCount = 0;
   CodeFileName = System_Argument("-code", "_CODE", argc, argv); 
}


void InitializeMachineOperations(void)
{
   int i,j;

   for (i=0, j=1; i < 47; i++, j++)
      String_Array_To_String_Constant (mach_op[i],j);
}



void InitializeNodeNames(void)
{
   int i,j;

   for (i=0, j=48; j <= NumberOfNodes; i++, j++)
      String_Array_To_String_Constant (node_name[i],j);
}



String MakeStringOf(int Number)
{
   Stack Temp;

   Temp = AllocateStack (50);
   ResetBufferInTextTable();
   if (Number == 0)
      AdvanceOnCharacter ('0');
   else
   {
      while (Number > 0)
      {
         Push (Temp,(Number % 10) + 48);
         Number /= 10;
      }

      while ( !(IsEmpty (Temp)))
         AdvanceOnCharacter ((char)(Pop(Temp)));
   }   
   return (ConvertStringInBuffer()); 
}  



void Reference(TreeNode T, Mode M, Clabel L)
{
   int Addr,OFFSET;
   String  Op;

   Addr = Decoration(Decoration(T));
   OFFSET = FrameDisplacement (Addr) ;
   switch (M)
   {
      case LeftMode  :  DecrementFrameSize();
                        if (ProcLevel (Addr) == 0) 
                           Op = SGVOP;
                        else
                           Op = SLVOP;
	                break;
      case RightMode :  IncrementFrameSize();
                        if (ProcLevel (Addr) == 0) 
                           Op = LGVOP;
          	        else
                           Op = LLVOP;
                        break;
   }
   CodeGen1 (Op,MakeStringOf(OFFSET),L);
}



int NKids (TreeNode T)
{
   return (Rank(T));
}


void Expression (TreeNode T, Clabel CurrLabel)
{
   int Kid,val,ind,looping_variable;
   Clabel Label1,Label2;
   String Mode;
   String Name1, Name2;
   char the_char;

   if (TraceSpecified)
   {
      fprintf (TraceFile, "<<< CODE GENERATOR >>> Processing Node ");
      Write_String (TraceFile, NodeName (T) );
      fprintf (TraceFile, " , Label is  ");
      Write_String (TraceFile, CurrLabel);
      fprintf (TraceFile, "\n");
   }

   switch (NodeName(T))
   {
      case LENode :  printf("1\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BLE, NoLabel);
         DecrementFrameSize();  printf("1 done\n");
         break;

      case EQNode :  printf("2\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BEQ, NoLabel);
         DecrementFrameSize();  printf("2 done\n");
         break;

      case NENode :  printf("3\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BNE, NoLabel);
         DecrementFrameSize();   printf("3 done\n");
         break;

      case GENode :  printf("4\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BGE, NoLabel);
         DecrementFrameSize();   printf("4 done\n");
         break;

      case LTNode :  printf("5\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BLT, NoLabel);
         DecrementFrameSize();   printf("5 done\n");
         break;

      case GTNode :  printf("6\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BGT, NoLabel);
         DecrementFrameSize();   printf("6 done\n");
         break;

      case PlusNode :   printf("7\n");
         Expression ( Child(T,1) , CurrLabel);
         if (Rank(T) == 2)
         {
            Expression ( Child(T,2) , NoLabel);
            CodeGen1 (BOPOP, BPLUS, NoLabel);
            DecrementFrameSize();
         }  printf("7 done\n");
         break;

      case MinusNode :  printf("8\n");
         Expression ( Child(T,1) , CurrLabel);
         if (Rank(T) == 2)
         {
            Expression ( Child(T,2) , NoLabel);
            CodeGen1 (BOPOP, BMINUS, NoLabel);
            DecrementFrameSize();
         }
         else
            CodeGen1 (UOPOP, UNEG, NoLabel);
         printf("8 done\n");break;

      case OrNode :  printf("9\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BOR, NoLabel);
         DecrementFrameSize();   printf("9 done\n");
         break;

      case MulNode : printf("10\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BMULT, NoLabel);
         DecrementFrameSize();   printf("10 done\n");
         break;

      case DivideNode : printf("11\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BDIV, NoLabel);
         DecrementFrameSize();   printf("11 done\n");
         break;

      case AndNode : printf("12\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BAND, NoLabel);
         DecrementFrameSize();   printf("12 done\n");
         break;

      case ModNode : printf("13\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BMOD, NoLabel);
         DecrementFrameSize();   printf("13 done\n");
         break;

      case NotNode : printf("14\n");
         Expression ( Child(T,1) , CurrLabel);
         CodeGen1 (UOPOP, UNOT, NoLabel);   printf("14 done\n");
         break;
      
      case PowerNode :  printf("15\n");
         Expression ( Child(T,1) , CurrLabel);
         Expression ( Child(T,2) , NoLabel);
         CodeGen1 (BOPOP, BEXP, NoLabel);
         DecrementFrameSize();   printf("15 done\n");
         break;

      case IntegerNode :   printf("16\n");
         CodeGen1 (LITOP, NodeName (Child(T,1)), CurrLabel);
         IncrementFrameSize();   printf("16 done\n");
         break;

      case CharNode: printf("17\n");
         CodeGen1 (LITOP, MakeStringOf((int)(Character(NodeName(Child(T,1)),2))), CurrLabel);
         IncrementFrameSize();   printf("17 done\n");
         break;

      case IdentifierNode :   printf("18\n");
         Mode = NodeName(Decoration(Child(Decoration(T),1)));Write_String (stdout,NodeName(Child(T,1)));printf("   the mode\n");  
         val = Decoration(Decoration(T));
         switch(Mode){
            case ConstNode :printf("in the const\n");
               CodeGen1 (LITOP,val,CurrLabel);
               break;
            case LitNode :printf("in the lit\n");
               CodeGen1 (LITOP,val,CurrLabel);
               break;
            case VarNode : printf("inside the var\n");
               Reference (T,RightMode,CurrLabel);
               break;
         } 
         IncrementFrameSize(); printf("18 done\n");
         break;


      case EofNode : printf("19\n");
         CodeGen1 (SOSOP, OSEOF, CurrLabel);
         IncrementFrameSize();   printf("19 done\n");
         break;

      case StringNode : printf("20\n");
         the_char = Character(NodeName(Child(T,1)),2);
         ind = 3;
         val = 1;
         while(the_char != '\"'){
            if(the_char != '\\'){
               if(val == 1){
                  CodeGen1 (LITOP, MakeStringOf((int)(the_char)), CurrLabel);
                  val = 0;
               }
               else{
                  CodeGen1 (LITOP, MakeStringOf((int)(the_char)), NoLabel);
               }
               CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
               the_char = Character(NodeName(Child(T,1)),ind);
               ind = ind + 1;
            }
            else{
               the_char =  Character(NodeName(Child(T,1)),ind); 
               switch(the_char){
                  case 't' : 
                     if(val == 1){
                        CodeGen1 (LITOP, MakeStringOf(9), CurrLabel);
                        CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
                        val = 0;
                     }
                     else{
                        CodeGen1 (LITOP, MakeStringOf(9), NoLabel);
                        CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
                     }
                     break;

                  case 'n' :
                     if(val == 1){
                        CodeGen1 (LITOP, MakeStringOf(10), CurrLabel);
                        CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
                        val = 0;
                     }
                     else{
                        CodeGen1 (LITOP, MakeStringOf(10), NoLabel);
                        CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
                     }
                     break;
               }
               ind = ind + 1;
               the_char = Character(NodeName(Child(T,1)),ind);
               ind = ind + 1;
            }
         }  printf("20 done\n");
         break;

      case SuccNode :   printf("21\n");
         Expression(Child(T,1),CurrLabel);
         CodeGen1 (LITOP, MakeStringOf(1), NoLabel);
         CodeGen1 (BOPOP, BPLUS, NoLabel);
         DecrementFrameSize();
         Name1 = NodeName(Child(Child(Decoration(T),1),1));
         if(Name1 != IntegerTNode && Name1 != CharTNode){
            CodeGen1 (LITOP, MakeStringOf(0), NoLabel);
            CodeGen1 (LITOP, MakeStringOf(NKids(Child(Decoration(T),2))), NoLabel);
            CodeGen0 (LIMITOP, NoLabel);
         }  printf("21 done\n");
         break;

      case PredNode: printf("22\n");
         Expression(Child(T,1),CurrLabel);
         CodeGen1 (LITOP, MakeStringOf(1), NoLabel);
         CodeGen1 (BOPOP, BMINUS, NoLabel);
         DecrementFrameSize();
         Name1 = NodeName(Child(Child(Decoration(T),1),1));
         if(Name1 != IntegerTNode && Name1 != CharTNode){
            CodeGen1 (LITOP, MakeStringOf(0), NoLabel);
            CodeGen1 (LITOP, MakeStringOf(NKids(Child(Decoration(T),2))), NoLabel);
            CodeGen0 (LIMITOP, NoLabel);
         }  printf("22 done\n");
         break;
      
      case OrdNode : printf("23\n");
         Expression(Child(T,1),CurrLabel);   printf("23 done\n");
         break;

      case ChrNode :    printf("24\n");
         Expression(Child(T,1),CurrLabel);   printf("24 done\n");
         break;

      case CallNode :   printf("51\n");
         CodeGen1 (LITOP,MakeStringOf(0),CurrLabel);
         IncrementFrameSize();
         Label2 = Decoration(Decoration(Child(Decoration(Child(T,1)),1)));
         for(Kid = 2;Kid <= NKids(T);Kid++){
            Expression(Child(T,Kid),NoLabel);
         }
         CodeGen1(CODEOP, Label2, NoLabel);
         for(Kid = 2;Kid <= NKids(T);Kid++){
            DecrementFrameSize();
         }
         CodeGen1(CALLOP,MakeStringOf(FrameSize-1),NoLabel);   printf("51 done\n");
         IncrementFrameSize();
         break;

      default :
         ReportTreeErrorAt(T);
         printf ("<<< CODE GENERATOR >>> : UNKNOWN NODE NAME ");
         Write_String (stdout,NodeName(T));
         printf ("\n");

   } /* end switch */
} /* end Expression */



Clabel ProcessNode (TreeNode T, Clabel CurrLabel)
{
   int Kid, Kid1, Kid2, Num, i,nn;
   Clabel Label1, Label2, Label3,Label4;
   String Name1;
   boolean otrws;

   if (TraceSpecified)
   {
      fprintf (TraceFile, "<<< CODE GENERATOR >>> Processing Node ");
      Write_String (TraceFile, NodeName (T) );
      fprintf (TraceFile, " , Label is  ");
      Write_String (TraceFile, CurrLabel);
      fprintf (TraceFile, "\n");
   }

   switch (NodeName(T))
   {
      case ProgramNode :   printf("25\n");
         CurrLabel = ProcessNode (Child(T,2),CurrLabel);
         CurrLabel = ProcessNode (Child(T,3),CurrLabel);
         CurrLabel = ProcessNode (Child(T,4),CurrLabel);
         CurrLabel = ProcessNode (Child(T,5),CurrLabel);
         Label1 = MakeLabel();
         CodeGen1 (GOTOOP, Label1, CurrLabel);
         CurrLabel = ProcessNode (Child(T,6),NoLabel);
         CurrLabel = ProcessNode(Child(T,7),Label1);   printf("25 done\n");
         return (CurrLabel);

      case TypesNode :  printf("26\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         printf("26 done\n");return (CurrLabel);

      case TypeNode :      printf("27\n");
         if(Rank(T) == 2){ printf("hello\n");
            Label1 = ProcessNode(Child(T,2), NoLabel);
         }   printf("27 done\n");
         return (CurrLabel);

      case DclnsNode :  printf("28\n");
         for (Kid = 1; Kid <= NKids(T); Kid++){
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         }
         if (NKids(T) > 0){   printf("28 done\n");
            return (NoLabel);
         }
         else{ printf("28 done\n");
            return (CurrLabel);
         }

      case VarNode : printf("29\n");
         for (Kid = 1; Kid < NKids(T); Kid++)
         {
            Num = MakeAddress();
            Decorate (Child(T,Kid), Num);
            if (Kid != 1)
               CodeGen1 (LITOP,MakeStringOf(0),NoLabel);
            else
               CodeGen1 (LITOP,MakeStringOf(0),CurrLabel);
            IncrementFrameSize();
         }  printf("29 done\n");
         return (NoLabel);                 

      case ConstsNode : printf("30\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         printf("30 done\n");return (CurrLabel);

      case ConstNode :  printf("31\n");
         Name1 = NodeName(Child(T,2));
         switch(Name1){
            case IntegerNode :   
               Decorate (Child(T,1), NodeName(Child(Child(T,2),1)));
               break;

            case CharNode: printf("the mso:");Write_String (stdout, NodeName(Child(Child(T,2),1)));printf("\n");
               Decorate (Child(T,1), MakeStringOf((int)(Character(NodeName(Child(Child(T,2),1)),2))));
               break;

            case IdentifierNode:
               Decorate (Child(T,1), Decoration(Decoration(Child(T,2))));
               break;
         }printf("31 done\n");
         return(CurrLabel);

      case LitNode : printf("32\n");
         Num = 0;
         for (Kid = 1; Kid <= NKids(T); Kid++)
         {
            Decorate (Child(T,Kid), MakeStringOf(Num));
            Num++;
         }  printf("32 done\n");
         return(CurrLabel);

      case BlockNode :  printf("33\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         CodeGen0 (NOP, CurrLabel);
         printf("33 done\n");return (NoLabel); 


      case AssignNode : printf("34\n");
         Expression (Child(T,2), CurrLabel);
         Reference (Child(T,1), LeftMode, NoLabel); 
         DecrementFrameSize();  printf("34 done\n");
         return (NoLabel);


      case SwapNode :   printf("35\n");
         Expression (Child(T,2), CurrLabel);
         Expression (Child(T,1), NoLabel);
         Reference (Child(T,2), LeftMode, NoLabel);
         DecrementFrameSize();
         Reference (Child(T,1), LeftMode, NoLabel); 
         DecrementFrameSize();  printf("35 done\n");
         return (NoLabel);

      case ReadNode :   printf("36\n");
         Name1 = NodeName(Child(T,1));printf("NodeName:");Write_String (stdout,Name1);printf("\n");
         switch(Name1){
            case IntegerTNode :  printf("the 1\n");
               CodeGen1 (SOSOP, OSINPUT, CurrLabel);
               CodeGen1 (SOSOP, OSOUTPUTL, NoLabel);
               Reference (Child(Child(T,1),1), LeftMode, NoLabel);
               break;

            case CharTNode :  printf("the 2\n");
               CodeGen1 (SOSOP, OSINPUTC, CurrLabel);
               CodeGen1 (SOSOP, OSOUTPUTL, NoLabel);
               Reference (Child(T,1), LeftMode, NoLabel);
               break;
         }

         for (Kid = 2; Kid <= NKids(T); Kid++)
         {
            Name1 = NodeName(Child(T,Kid));printf("NodeName:");Write_String (stdout,Name1);printf("\n");
            switch(Name1){
               case IntegerTNode : printf("the 1\n");
                  CodeGen1 (SOSOP, OSINPUT, NoLabel);
                  CodeGen1 (SOSOP, OSOUTPUTL, NoLabel);
                  Reference (Child(Child(T,Kid),1), LeftMode, NoLabel);
                  break;

               case CharTNode : printf("the 2\n");
                  CodeGen1 (SOSOP, OSINPUTC, NoLabel);
                  CodeGen1 (SOSOP, OSOUTPUTL, NoLabel);
                  Reference (Child(Child(T,Kid),1), LeftMode, NoLabel);
                  break;
            }
         }  printf("36 done\n");
         return (NoLabel);

      case OutputNode : printf("37\n");
         Expression (Child(Child(T,1),1), CurrLabel);
         Name1 = NodeName(Child(T,1));
         switch(Name1){
            case IntegerTNode :
               CodeGen1 (SOSOP, OSOUTPUT, NoLabel);
               break;
            case CharTNode :
               CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
               break;
         }
         
         DecrementFrameSize();
         for (Kid = 2; Kid <= NKids(T); Kid++)
         {
            Expression (Child(Child(T,Kid),1), NoLabel);
            Name1 = NodeName(Child(T,Kid));
            switch(Name1){
               case IntegerTNode :
                  CodeGen1 (SOSOP, OSOUTPUT, NoLabel);
                  break;
               case CharTNode :
                  CodeGen1 (SOSOP, OSOUTPUTC, NoLabel);
                  break;  
            }
            DecrementFrameSize();
         }
         CodeGen1 (SOSOP, OSOUTPUTL, NoLabel);  printf("37 done\n");
         return (NoLabel);


      case IfNode :  printf("38\n");
         Expression (Child(T,1), CurrLabel);
         Label1 = MakeLabel();
         Label2 = MakeLabel();
         Label3 = MakeLabel();
         CodeGen2 (CONDOP,Label1,Label2, NoLabel);
         DecrementFrameSize();
         CodeGen1 (GOTOOP, Label3, ProcessNode (Child(T,2), Label1));
         if (Rank(T) == 3)
            CodeGen0 (NOP, ProcessNode (Child(T,3),Label2));
         else
            CodeGen0 (NOP, Label2);
         printf("38 done\n");return (Label3);                


      case WhileNode :  printf("39\n");
         if (CurrLabel == NoLabel) 
            Label1 = MakeLabel();
         else 
            Label1 = CurrLabel;
         Label2 = MakeLabel();
         Label3 = MakeLabel();
         Expression (Child(T,1), Label1);
         CodeGen2 (CONDOP, Label2, Label3, NoLabel);
         DecrementFrameSize();
         CodeGen1 (GOTOOP, Label1, ProcessNode (Child(T,2), Label2) );  printf("39 done\n");
         return (Label3);


       case RepeatNode :   printf("40\n");
         if(CurrLabel == NoLabel)
            Label2 = MakeLabel();
         else
            Label2 = CurrLabel;
         Label1 = MakeLabel();
         CurrLabel = Label2;
         for (Kid = 1; Kid <= NKids(T) - 1; Kid++)
         {
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         }
         Expression (Child(T,NKids(T)), CurrLabel);
         CodeGen2 (CONDOP, Label1, Label2, NoLabel);
         DecrementFrameSize();   printf("40 done\n");
         return(Label1);

       case LoopNode :  printf("41\n");
         if(Decoration(T) == 0)
            Label1 = NoLabel;
         else
            Label1 = MakeLabel();
         Decorate(T,Label1);
         if(CurrLabel == NoLabel)
            Label2 = MakeLabel();
         else
            Label2 = CurrLabel;
         CurrLabel = Label2;
         for (Kid = 1; Kid <= NKids(T); Kid++)
         {
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         }
         CodeGen1 (GOTOOP, Label2, CurrLabel);  printf("41 done\n");
         return(Label1);


       case ExitNode :  printf("42\n");
         Label1 = Decoration(Decoration(T));
         CodeGen1 (GOTOOP, Label1, CurrLabel);  printf("42 done\n");
         return(NoLabel);

       case UptoNode :
       case DowntoNode :   printf("43\n");
         Expression(Child(T,3), CurrLabel);
         Expression(Child(T,2), NoLabel);
         Reference (Child(T,1), LeftMode, NoLabel);
         DecrementFrameSize();
         Label1 = MakeLabel();
         Label2 = MakeLabel();
         Label3 = MakeLabel();
         CodeGen0(DUPOP, Label1);
         IncrementFrameSize();
         Expression(Child(T,1),NoLabel);
         if(NodeName(T) == UptoNode){
            CodeGen1 (BOPOP, BGE, NoLabel);
         }
         else{
            CodeGen1 (BOPOP, BLE, NoLabel);
         }
         DecrementFrameSize();
         CodeGen2 (CONDOP,Label2,Label3, NoLabel);
         DecrementFrameSize();
         Label4 = ProcessNode(Child(T,4),Label2);
         Expression(Child(T,1),Label4);
         if(NodeName(T) == UptoNode){
            CodeGen1 (UOPOP, USUCC, NoLabel);
         }
         else{
            CodeGen1 (UOPOP, UPRED, NoLabel);
         }
         Reference (Child(T,1), LeftMode, NoLabel);
         DecrementFrameSize();
         CodeGen1 (GOTOOP, Label1, NoLabel);
         CodeGen1 (POPOP, MakeStringOf(1), Label3);
         DecrementFrameSize();
         CodeGen1 (LITOP, MakeStringOf(0), NoLabel);
         Reference (Child(T,1), LeftMode, NoLabel);   printf("43 done\n");
         return(NoLabel);


       case CaseNode :  printf("44\n");
         Expression(Child(T,1), CurrLabel);
         Label4 = MakeLabel();
         Label1 = MakeLabel();
         Label2 = MakeLabel();

         if(NodeName(Child(Child(T,2),1)) == RangeClauseNode){
            CodeGen0(DUPOP, NoLabel);
            IncrementFrameSize();
            CodeGen0(DUPOP, NoLabel);
            IncrementFrameSize();
            Expression(Child(Child(Child(T,2),1),1),NoLabel);
            CodeGen1(BOPOP, BGE, NoLabel);
            DecrementFrameSize();
            CodeGen0(SWAPOP, NoLabel);
            Expression(Child(Child(Child(T,2),1),2),NoLabel);
            CodeGen1(BOPOP, BLE, NoLabel);
            DecrementFrameSize();
            CodeGen1(BOPOP, BAND, NoLabel);
            DecrementFrameSize();
         }
         else{
            CodeGen0(DUPOP, NoLabel);
            IncrementFrameSize();
            Expression(Child(Child(T,2),1),NoLabel);
            CodeGen1(BOPOP, BEQ, NoLabel);
            DecrementFrameSize();
         }
         CodeGen2 (CONDOP, Label1, Label2, NoLabel);
         DecrementFrameSize();
         CodeGen1 (POPOP, MakeStringOf(1), Label1);
         DecrementFrameSize();
         Label3 = ProcessNode(Child(Child(T,2),2),NoLabel);
         CodeGen1 (GOTOOP, Label4, Label3);
         CurrLabel = Label2;


         if(NodeName(Child(T,NKids(T))) == OtherwiseNode){
            otrws = true;
            nn = NKids(T)-1;
         }
         else{
            otrws = false;
            nn = NKids(T);
         }
         
         for(i = 3;i<=nn;i++){
               Label1 = MakeLabel();
               Label2 = MakeLabel();
               if(NodeName(Child(Child(T,i),1)) == RangeClauseNode){
                  CodeGen0(DUPOP, CurrLabel);
                  IncrementFrameSize();
                  CodeGen0(DUPOP, NoLabel);
                  IncrementFrameSize();
                  Expression(Child(Child(Child(T,i),1),1),NoLabel);
                  CodeGen1(BOPOP, BGE, NoLabel);
                  DecrementFrameSize();
                  CodeGen0(SWAPOP, NoLabel);
                  Expression(Child(Child(Child(T,i),1),2),NoLabel);
                  CodeGen1(BOPOP, BLE, NoLabel);
                  DecrementFrameSize();
                  CodeGen1(BOPOP, BAND, NoLabel);
                  DecrementFrameSize();
               }
               else{
                  CodeGen0(DUPOP, CurrLabel);
                  IncrementFrameSize();
                  Expression(Child(Child(T,i),1),NoLabel);
                  CodeGen1(BOPOP, BEQ, NoLabel);
                  DecrementFrameSize();
               }
               CodeGen2 (CONDOP, Label1, Label2, NoLabel);
               DecrementFrameSize();
               CodeGen1 (POPOP, MakeStringOf(1), Label1);
               DecrementFrameSize();
               Label3 = ProcessNode(Child(Child(T,i),2),NoLabel);
               CodeGen1 (GOTOOP, Label4, Label3);
               CurrLabel = Label2;
         }

         if(otrws){
            CodeGen1 (POPOP, MakeStringOf(1), CurrLabel);
            DecrementFrameSize();
            Label3 = ProcessNode(Child(Child(T,NKids(T)),1),NoLabel);
            CodeGen0(NOP, Label3);
         }
         else{
            CodeGen1 (POPOP, MakeStringOf(1), CurrLabel);
            DecrementFrameSize();
         }  printf("44 done\n");
         return(Label4);

       case NullNode :  printf("45\n"); printf("45 done\n");
         return(CurrLabel);

 
      case SubprogsNode :  printf("46\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            CurrLabel = ProcessNode (Child(T,Kid), CurrLabel);
         printf("46 done\n");return (CurrLabel);

      case FcnNode : printf("47\n");
         OpenFrame();
         Decorate(Child(T,1),MakeAddress());
         IncrementFrameSize();
         Label2 = MakeLabel();
         Decorate(T,Label2);
         for(Kid = 1;Kid <= NKids(Child(T,2)); Kid++){
            for(Kid1 = 1;Kid1 <= NKids(Child(Child(T,2),Kid))-1;Kid1++){
               Num = MakeAddress();
               Decorate (Child(Child(Child(T,2),Kid),Kid1), Num);
               IncrementFrameSize();
            }
         }
         CurrLabel = ProcessNode(Child(T,4),CurrLabel);
         CurrLabel = ProcessNode(Child(T,5),CurrLabel);
         CurrLabel = ProcessNode(Child(T,6),Label2);
         CurrLabel = ProcessNode(Child(T,7),CurrLabel);
         CodeGen1(LLVOP, MakeStringOf(0),CurrLabel);
         CodeGen1(RTNOP, MakeStringOf(1), NoLabel);
         CloseFrame();  printf("47 done\n");
         return(NoLabel);

      case ProcedureNode : printf("48\n");
         OpenFrame();
         Label2 = MakeLabel();
         Decorate(T,Label2);
         for(Kid = 1;Kid <= NKids(Child(T,2)); Kid++){
            for(Kid1 = 1;Kid1 <= NKids(Child(Child(T,2),Kid))-1;Kid1++){
               Num = MakeAddress();printf("in the makeaddress:%d\n",Num);
               Decorate (Child(Child(Child(T,2),Kid),Kid1), Num);
               IncrementFrameSize();
            }
         }
         CurrLabel = ProcessNode(Child(T,3),CurrLabel);
         CurrLabel = ProcessNode(Child(T,4),CurrLabel);
         CurrLabel = ProcessNode(Child(T,5),Label2);
         CurrLabel = ProcessNode(Child(T,6),CurrLabel);
         CodeGen1(RTNOP, MakeStringOf(0), NoLabel);
         CloseFrame();  printf("48 done\n");
         return(NoLabel);

      case CallNode :   printf("49\n");
         if(NodeName(Decoration(Child(Decoration(Child(T,1)),1))) != ProcedureNode){
            CodeGen1 (LITOP,MakeStringOf(0),CurrLabel);
            IncrementFrameSize();
         }
         Label2 = Decoration(Decoration(Child(Decoration(Child(T,1)),1)));
         for(Kid = 2;Kid <= NKids(T);Kid++){
            Expression(Child(T,Kid),NoLabel);
         }
         CodeGen1(CODEOP, Label2, NoLabel);
         for(Kid = 2;Kid <= NKids(T);Kid++){
            DecrementFrameSize();
         }
         if(NodeName(Decoration(Child(Decoration(Child(T,1)),1))) != ProcedureNode){
            CodeGen1(CALLOP,MakeStringOf(FrameSize-1),NoLabel);
         }
         else{
            CodeGen1(CALLOP,MakeStringOf(FrameSize),NoLabel);   
         }  printf("49 done\n");
         return(NoLabel);

      case ReturnNode : printf("50\n");
         Expression(Child(T,1),CurrLabel);
         CodeGen1(RTNOP,MakeStringOf(1), NoLabel);
         DecrementFrameSize();   printf("50 done\n");
         return(NoLabel);

      default :
              ReportTreeErrorAt(T);
              printf ("<<< CODE GENERATOR >>> : UNKNOWN NODE NAME ");
              Write_String (stdout,NodeName(T));
              printf ("\n");

   } /* end switch */
}   /* end ProcessNode */


