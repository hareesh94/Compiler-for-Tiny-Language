#include <stdio.h>
#include <header/Open_File.h>
#include <header/CommandLine.h>
#include <header/Table.h>
#include <header/Text.h>
#include <header/Error.h>
#include <header/String_Input.h> 
#include <header/Tree.h>
#include <header/Dcln.h>
#include <header/Constrainer.h>

#define ProgramNode    1
#define TypesNode      2
#define TypeNode       3
#define DclnsNode      4
#define VarNode        5
#define IntegerTNode   6
#define BooleanTNode   7
#define BlockNode      8
#define AssignNode     9
#define OutputNode     10
#define IfNode         11
#define WhileNode      12
#define NullNode       13
#define LENode         14
#define PlusNode       15
#define MinusNode      16
#define ReadNode       17
#define IntegerNode    18
#define IdentifierNode 19
#define EofNode        20  
#define BooleanNodeTrue  21
#define BooleanNodeFalse 22 
#define EQNode          23
#define NENode          24
#define GENode          25
#define LTNode          26
#define GTNode          27
#define NotNode         28
#define ModNode         29
#define AndNode         30
#define OrNode          31
#define MulNode         32
#define PowerNode       33
#define DivideNode      34
#define SwapNode        35
#define RepeatNode      36
#define LoopNode        37
#define ExitNode        38
#define UptoNode        39
#define DowntoNode      40
#define CaseNode        41
#define CaseClauseNode  42
#define OtherwiseNode   43
#define RangeClauseNode 44
#define CharTNode       45
#define CharNode        46
#define ConstsNode      47
#define ConstNode       48
#define LitNode         49
#define SuccNode        50
#define PredNode        51
#define OrdNode         52
#define ChrNode         53
#define OutputTypeNode  54
#define StringNode      55
#define StringTNode     56
#define CallNode        57
#define FcnNode         58
#define ProcedureNode   59
#define SubprogsNode    60
#define ParamsNode      61
#define ReturnNode      62

#define NumberOfNodes  62

#define LOOP_CTXT    63
#define FOR_CTXT     64
#define S_CTXT       65

typedef TreeNode UserType;

/****************************************************************
 Add new node names to the end of the array, keeping in strict
  order with the define statements above, then adjust the i loop
  control variable in InitializeConstrainer().
*****************************************************************/
char *node[] = { "program", "types", "type", "dclns",
                 "var", "integer", "boolean", "block",
                 "assign", "output", "if", "while", 
                 "<null>", "<=", "+", "-", "read",
                 "<integer>", "<identifier>", "eof", "true", "false" 
                 , "=", "<>", ">=", "<", ">", "not", "mod",
                  "and", "or", "*", "exp", "/", "swap", "repeat",
                 "loop", "exit", "upto", "downto", "case", "case_clause", "otherwise", "range",
                 "char","<char>","consts", "const", "lit", "succ", "pred", "ord", "chr", "type_disambiguation",
                 "<string>", "string", "call", "function", "procedure", "subprogs", "params", "return"};


UserType TypeInteger, TypeBoolean, TypeChar, TypeString;
boolean TraceSpecified;
FILE *TraceFile;
char *TraceFileName;
int NumberTreesRead, index;


void Constrain(void)    
{
   int i;
   InitializeDeclarationTable();
   Tree_File = Open_File("_TREE", "r"); 
   NumberTreesRead = Read_Trees();
   fclose (Tree_File);                     

   AddIntrinsics();

#if 0
   printf("CURRENT TREE\n");
   for (i=1;i<=SizeOf(Tree);i++)
      printf("%2d: %d\n",i,Element(Tree,i));
#endif

   ProcessNode(RootOfTree(1)); 
   ModeFunction(RootOfTree(1));

    
   Tree_File = fopen("_TREE", "w");  
   Write_Trees();
   fclose (Tree_File);                   

   if (TraceSpecified)
      fclose(TraceFile);    
}


void InitializeConstrainer (int argc, char *argv[])
{          
   int i, j;

   InitializeTextModule();
   InitializeTreeModule();
   for (i=0, j=1; i<NumberOfNodes; i++, j++)
      String_Array_To_String_Constant (node[i], j); 
   
   index = System_Flag ("-trace", argc, argv);
 
   if (index)                                       
   {
      TraceSpecified = true; 
      TraceFileName = System_Argument ("-trace", "_TRACE", argc, argv);
      TraceFile = Open_File(TraceFileName, "w");
   }
   else
      TraceSpecified = false;          
}                        


void AddIntrinsics (void)
{
   TreeNode TempTree;

   AddTree (TypesNode, RootOfTree(1), 2);

   TempTree = Child (RootOfTree(1), 2);
   AddTree (TypeNode, TempTree, 1);

   TempTree = Child (RootOfTree(1), 2);
   AddTree (TypeNode, TempTree, 1);

   TempTree = Child (RootOfTree(1), 2);
   AddTree (TypeNode, TempTree, 1);

   TempTree = Child (RootOfTree(1), 2);
   AddTree (TypeNode, TempTree, 1);

   TempTree = Child (Child (RootOfTree(1), 2), 1);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 1), 1);
   AddTree(BooleanTNode, TempTree, 1);
   TempTree = Child (Child (RootOfTree(1), 2), 1);
   AddTree (LitNode, TempTree, 2);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 1), 2);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 1), 2);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child(Child (Child (RootOfTree(1), 2), 1), 2), 1);
   AddTree (BooleanNodeFalse, TempTree, 1);
   TempTree = Child(Child(Child (Child (RootOfTree(1), 2), 1), 2), 2);
   AddTree (BooleanNodeTrue, TempTree, 1);
   
 
   TempTree = Child (Child (RootOfTree(1), 2), 2);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 2), 1);
   AddTree(IntegerTNode, TempTree, 1);

   TempTree = Child (Child (RootOfTree(1), 2), 3);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 3), 1);
   AddTree(CharTNode, TempTree, 1);

   TempTree = Child (Child (RootOfTree(1), 2), 4);
   AddTree (IdentifierNode, TempTree, 1);
   TempTree = Child(Child (Child (RootOfTree(1), 2), 4), 1);
   AddTree(StringTNode, TempTree, 1);


   TypeBoolean = Child(Child(Child(Child (RootOfTree(1), 2),1),1),1);
   TypeInteger = Child(Child(Child(Child (RootOfTree(1), 2),2),1),1);
   TypeChar    = Child(Child(Child(Child (RootOfTree(1), 2),3),1),1);
   TypeString  = Child(Child(Child(Child (RootOfTree(1), 2),4),1),1);
}



void ErrorHeader (TreeNode T)
{ 
   printf ("<<< CONSTRAINER ERROR >>> AT ");
   Write_String (stdout,SourceLocation(T));
   printf (" : ");
   printf ("\n");
}


int NKids (TreeNode T)
{
   return (Rank(T));
}



UserType Expression (TreeNode T)
{
   UserType Type1, Type2,Type3;
   TreeNode Declaration, Temp1, Temp2;
   String Name1, Name2, Mode;
   int NodeCount,N,Kid,Kid1,Kid2;

   if (TraceSpecified)
   {
      fprintf (TraceFile, "<<< CONSTRAINER >>> : Expn Processor Node ");
      Write_String (TraceFile, NodeName(T));
      fprintf (TraceFile, "\n");
   }
     
   switch (NodeName(T))
   {
      case LENode :   printf("1\n"); 
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '<=' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("1 done\n");
         return (TypeBoolean);


      case EQNode :   printf("2\n"); 
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '=' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("2 done\n");
         return (TypeBoolean);

      case NENode : printf("3\n");   
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '<>' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("3 done\n");
         return (TypeBoolean);
      
      case GENode :  printf("4\n");    
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '>=' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("4 done\n");
         return (TypeBoolean);

      case LTNode :   printf("5\n");
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '<' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("5 done\n");
         return (TypeBoolean);

      case GTNode :  printf("6\n");
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if(Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '>' MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("6 done\n");
         return (TypeBoolean);

      case PlusNode :
      case MinusNode :  printf("72\n");
         Type1 = Expression (Child(T,1));

         if (Rank(T) == 2){
            Type2 = Expression (Child(T,2));
         }
         else  {
            Type2 = Type1;
         }

         if (Type1 != Type2)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '+', '-', '*', '/', mod ");
            printf ("MUST BE OF SAME TYPE\n");
            printf ("\n");
         }  printf("72 done\n");
         return (Type1);

      case MulNode :
      case DivideNode : 
      case ModNode : printf("7\n");
         Type1 = Expression (Child(T,1));

         if (Rank(T) == 2){
            Type2 = Expression (Child(T,2));
         }
         else  {
            Type2 = TypeInteger;
         }

         if (Type1 != TypeInteger || Type2 != TypeInteger)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '+', '-', '*', '/', mod ");
            printf ("MUST BE TYPE INTEGER\n");
            printf ("\n");
         }  printf("7 done\n");
         return (TypeInteger);

 
      case OrNode :  printf("8\n");  
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if (Type1 != TypeBoolean || Type2 != TypeBoolean)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF 'or' MUST BE TYPE BOOLEAN\n");
            printf ("\n");
         }  printf("8 done\n");
         return (TypeBoolean);

      case AndNode :  printf("9\n");  
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if (Type1 != TypeBoolean || Type2 != TypeBoolean)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF 'and' MUST BE TYPE BOOLEAN\n");
            printf ("\n");
         }  printf("9 done\n");
         return (TypeBoolean);

      case NotNode :    printf("10\n");
         Type1 = Expression (Child(T,1));

         if (Type1 != TypeBoolean)
         {
            ErrorHeader(Child(T,1));
            printf ("THE ARGUMENT OF 'not' MUST BE TYPE BOOLEAN\n");
            printf ("\n");
         }  printf("10 done\n");
         return (TypeBoolean);

      case PowerNode :    printf("11\n");
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));

         if (Type1 != TypeInteger || Type2 != TypeInteger)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF '**' MUST BE TYPE INTEGER\n");
            printf ("\n");
         }  printf("11 done\n");
         return (TypeInteger);


      case IntegerNode : printf("12\n");  printf("12 done\n");
         return (TypeInteger);

      case CharNode :   printf("13\n");   printf("13 done\n");
         return (TypeChar);

      case IdentifierNode :   printf("14\n");Write_String (stdout,NodeName(Child(T,1)));printf(".........................\n");
         Declaration = Lookup (NodeName(Child(T,1)), T);
         if (Declaration != NullDeclaration)
         {
            Decorate (T, Declaration); printf("14 done\n");printf("the return type:");Write_String (stdout,NodeName(Decoration(Declaration)));printf("\n");
            return (Decoration(Declaration));
         }
         else{ printf("14 done\n");
            return (TypeInteger);
         }


      case SuccNode :   printf("15\n");
         Type1 = Expression (Child(T,1));
         Decorate(T,Decoration(Type1));   printf("15 done\n");
         return(Type1);

      case PredNode: printf("16\n");
         Type1 = Expression (Child(T,1));
         Decorate(T,Decoration(Type1));   printf("16 done\n");
         return(Type1);
      
      case OrdNode :    printf("17\n");
         Type1 = Expression (Child(T,1)); printf("17 done\n");
         return(TypeInteger);

      case ChrNode :    printf("18\n");
         Type1 = Expression (Child(T,1));
         if (Type1 != TypeInteger)
         {
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF CHR MUST BE TYPE INTEGER\n");
            printf ("\n");
         }  printf("18 done\n");
         return(TypeChar);

      case StringNode : printf("19\n");   printf("19 done\n");
         return(TypeString);

      case EofNode : printf("20\n");   printf("20 done\n");
         return (TypeBoolean);

      case CallNode :   printf("71\n");
         Type1 = Expression(Child(T,1));
         Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
         if(Mode != FcnNode){
            ErrorHeader(T);
            printf ("FUNCTION CALL AS AN EXPRESSION CANNOT HAVE ANYTHING OTHER THAN A FUNCTION MODE\n");
            printf ("\n");
         }
         Temp1 = Decoration(Child(T,1));
         Temp1 = Child(Decoration(Child(Temp1,1)),2);
         N = 0;
         for(Kid = 1;Kid<=NKids(Temp1);Kid++){
            N = N + NKids(Child(Temp1,Kid)) - 1;
         }
         if(N != (NKids(T) -1) ){
            ErrorHeader(T);
            printf ("NUMBER OF PARAMETERS DO NOT MATCH\n");
            printf ("\n");
         }
         else{
            for(Kid = 2;Kid<=NKids(T);Kid++){printf("kidNo:%d\n",Kid);
               Type2 = Expression(Child(T,Kid));printf("the type of stuff:");Write_String (stdout,NodeName(Type2));printf("\n");
               N = 1;
               for(Kid1 = 1;Kid1<=NKids(Temp1);Kid1++){
                  for(Kid2 = 1;Kid2<=NKids(Child(Temp1,Kid1))-1;Kid2++){printf("Name of where we are:");Write_String (stdout,NodeName(Child(Child(Child(Temp1,Kid1),Kid2),1)));printf("\n");
                     printf("value of nis:%d\n",N);   
                     if(N == Kid -1){
                        Type3 = Decoration(Child(Child(Temp1,Kid1),Kid2));
                        N = -1;
                        break;
                     }
                     N++;
                  }
                  if(N == -1){
                     break;
                  }
               }printf("type2:");Write_String (stdout,NodeName(Type2));printf("\ttype3:");Write_String (stdout,NodeName(Type3));printf("\n");
               if(Type2 != Type3){
                  ErrorHeader(T);
                  printf ("PARAMETER TYPES DO NOT MATCH\n");
                  printf ("\n");
               }
            }
         }  printf("71 done\n");
         return(Type1);

      default :
         ErrorHeader(T);
         printf ("UNKNOWN NODE NAME");
         Write_String (stdout,NodeName(T));
         printf ("\n");

   }  /* end switch */
}  /* end Expression */




void ProcessNode (TreeNode T) 
{
   int Kid,Kid1,Kid2, N, i,nn;
   String Name1, Name2, Mode;
   TreeNode Type1, Type2, Type3,Temp;
   boolean otrws;

   if (TraceSpecified)
   {
      fprintf (TraceFile,
               "<<< CONSTRAINER >>> : Stmt Processor Node ");
      Write_String (TraceFile, NodeName(T));
      fprintf (TraceFile, "\n");
   }

   switch (NodeName(T))
   {
      case ProgramNode :   printf("21\n");
         DTEnter(S_CTXT,T,T);
         OpenScope();
         Name1 = NodeName(Child(Child(T,1),1));
         Name2 = NodeName(Child(Child(T,NKids(T)),1));

         if (Name1 != Name2)
         {
           ErrorHeader(T);
           printf ("PROGRAM NAMES DO NOT MATCH\n");
           printf ("\n");
         }
         DTEnter(LOOP_CTXT,T,T); 
         DTEnter(FOR_CTXT,T,T); 
         for (Kid = 2; Kid <= NKids(T)-1; Kid++)
            ProcessNode (Child(T,Kid));
         CloseScope();  printf("21 done\n");
         break;


      case TypesNode :  printf("22\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            ProcessNode (Child(T,Kid));
         printf("22 done\n"); break;


      case TypeNode :   printf("23\n");
         DTEnter (NodeName(Child(Child(T,1),1)),Child(T,1),T);
         Decorate (Child(T,1), Child(Child(T,1),1));
         Decorate (Child(Child(T,1),1), T);

         if(Rank(T) == 2){
            ProcessNode(Child(T,2));
            for (Kid  = 1; Kid <= NKids(Child(T,2)); Kid++)
            {
               Decorate (Child(Child(T,2),Kid), Child(Child(T,1),1));
            }

         }  printf("23 done\n");
         break;


      case LitNode:  printf("24\n");
         for (Kid  = 1; Kid <= NKids(T); Kid++)
         {
            DTEnter (NodeName(Child(Child(T,Kid),1)), Child(T,Kid), T);
            Decorate (Child(T,Kid), T);
            Decorate (Child(Child(T,Kid),1), T);

         }  printf("24 done\n");
         break;

      case ConstsNode :    printf("25\n");
         for (Kid = 1; Kid <= NKids(T); Kid++){
            ProcessNode(Child(T,Kid));
         }  printf("25 done\n");
         break;

      case ConstNode :  printf("26\n");
         Type1 = Expression (Child(T,2));

         DTEnter (NodeName(Child(Child(T,1),1)), Child(T,1), T);
         Decorate (Child(T,1), Type1);
         Decorate (Child(Child(T,1),1), T);  printf("26 done\n");
         break;

      case DclnsNode :  printf("27\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            ProcessNode (Child(T,Kid));
         printf("27 done\n");   break;


      case VarNode : printf("28\n");
         Type1 = Expression(Child(T, NKids(T)));

         for (Kid  = 1; Kid < NKids(T); Kid++)
         {
            DTEnter (NodeName(Child(Child(T,Kid),1)), Child(T,Kid), T);
            Decorate (Child(T,Kid), Type1);
            Decorate (Child(Child(T,Kid),1), T);

         }  printf("28 done\n");
         break;


      case BlockNode :  printf("29\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
            ProcessNode (Child(T,Kid));
         printf("29 done\n"); break;


      case AssignNode : printf("30\n");
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));
         Name1 = NodeName(Type1);
         Name2 = NodeName(Type2);

         if (Type1 != Type2)
         {
            ErrorHeader(T);
            printf ("ASSIGNMENT TYPES DO NOT MATCH\n");
            printf ("\n");
         }

         Temp = Lookup(FOR_CTXT,T);
         
        
         while(NodeName(Temp) != ProgramNode){
            if(NodeName(Child(Child(Temp,1),1)) == NodeName(Child(Child(T,1),1))){
               ErrorHeader(T);
               printf ("THE LOOP VARIABLE RE-ASSIGNED INSIDE THE FOR LOOP\n");
               printf ("\n");
            }
            Temp = Decoration(Temp);
         }
         printf("30 done\n");
         break;


      case SwapNode :   printf("31\n");
         Type1 = Expression (Child(T,1));
         Type2 = Expression (Child(T,2));
         Name1 = NodeName(Type1);
         Name2 = NodeName(Type2);

         if (Type1 != Type2)
         {
            ErrorHeader(T);
            printf ("ASSIGNMENT TYPES DO NOT MATCH\n");
            printf ("\n");
         }

         Temp = Lookup(FOR_CTXT,T);
         
        
         while(NodeName(Temp) != ProgramNode){
            if(NodeName(Child(Child(Temp,1),1)) == NodeName(Child(Child(T,1),1))){
               ErrorHeader(T);
               printf ("THE LOOP VARIABLE SWAPPED INSIDE THE FOR LOOP\n");
               printf ("\n");
            }
            Temp = Decoration(Temp);
         }  printf("31 done\n");
         break;

      case ReadNode :   printf("32\n");
         for (Kid = 1; Kid <= NKids(T); Kid++){
            Type1 = Expression (Child(Child(T,Kid),1));
            if (Type1 != TypeInteger && Type1 != TypeChar)
            {
               ErrorHeader(T);
               printf ("INPUT EXPRESSION MUST BE TYPE INTEGER OR CHAR\n");
               printf ("\n");
            }
            Name1 = NodeName(Type1);
            switch(Name1){
               case IntegerTNode : 
                  ChangeNodeName(Child(T,Kid), IntegerTNode);
                  break;

               case CharTNode :
                  ChangeNodeName(Child(T,Kid), CharTNode);
                  break;

               case StringTNode :
                  ChangeNodeName(Child(T,Kid), StringTNode);
                  break;

            }
         }

         Temp = Lookup(FOR_CTXT,T);
         
        
         while(NodeName(Temp) != ProgramNode){
            for (Kid = 1; Kid <= NKids(T); Kid++)
            {
               if(NodeName(Child(Child(Temp,1),1)) == NodeName(Child(Child(Child(T,Kid),1),1))){   
                  ErrorHeader(T);
                  printf ("THE LOOP VARIABLE READ INSIDE THE FOR LOOP\n");
                  printf ("\n");
               }
            }
            Temp = Decoration(Temp);
         }  printf("32 done\n");
         break;

      case OutputNode : printf("33\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
         {
            Type1 = Expression(Child(Child(T,Kid),1));
            if(Type1 != TypeChar && Type1 != TypeInteger && Type1 != TypeString){
               ErrorHeader(T);
               printf ("OUTPUT NODE");
               printf (" IS NOT TYPE CHAR OR INTEGER\n");
               printf ("\n");
            }
            Name1 = NodeName(Type1);
            switch(Name1){
               case IntegerTNode : 
                  ChangeNodeName(Child(T,Kid), IntegerTNode);
                  break;

               case CharTNode :
                  ChangeNodeName(Child(T,Kid), CharTNode);
                  break;

               case StringTNode :
                  ChangeNodeName(Child(T,Kid), StringTNode);
                  break;

            }
         }  printf("33 done\n");
         break;

      case IfNode :  printf("34\n");
         if (Expression (Child(T,1)) != TypeBoolean)
         {
            ErrorHeader(T);
            printf ("CONTROL EXPRESSION OF 'IF' STMT");
            printf (" IS NOT TYPE BOOLEAN\n");
            printf ("\n");
         } 

         ProcessNode (Child(T,2));
         if (Rank(T) == 3)
            ProcessNode (Child(T,3));
         printf("34 done\n");break;


      case WhileNode :  printf("35\n");
         if (Expression (Child(T,1)) != TypeBoolean)
         {
            ErrorHeader(T);
            printf ("WHILE EXPRESSION NOT OF TYPE BOOLEAN\n");
            printf ("\n");
         }
         ProcessNode (Child(T,2));  printf("35 done\n");
         break;


      case RepeatNode : printf("36\n");
         if (Expression (Child(T,NKids(T))) != TypeBoolean)
         {
            ErrorHeader(T);
            printf ("REPEAT EXPRESSION NOT OF TYPE BOOLEAN\n");
            printf ("\n");
         }

         for (Kid = 1; Kid <= NKids(T) - 1; Kid++)
            ProcessNode (Child(T,Kid));
         printf("36 done\n");break;

      case LoopNode :   printf("37\n");
         OpenScope();
         DTEnter(LOOP_CTXT,T,T);

         for (Kid = 1; Kid <= NKids(T); Kid++)
            ProcessNode (Child(T,Kid));
         CloseScope();
         if(Decoration(T) == 0){
            printf("Warning: No exit\n");
         }  printf("37 done\n");
         break;

      case ExitNode :   printf("38\n");
         Temp = Lookup(LOOP_CTXT,T);
         if(NodeName(Temp) != LoopNode){
            ErrorHeader(T);
            printf ("EXIT DOES NOT CORRESPOND TO A LOOP\n");
            printf ("\n");
         }
         Decorate(T,Temp);
         Decorate(Temp,T); printf("38 done\n");
         break;

      case UptoNode :
      case DowntoNode:  printf("39\n");
         Temp = Lookup(FOR_CTXT,T);
         Decorate(T,Temp);
         OpenScope();
         DTEnter(FOR_CTXT,T,T);
         DTEnter(LOOP_CTXT,T,T);
         
         if(Expression(Child(T,2)) != Expression(Child(T,1))){
            ErrorHeader(T);
            printf ("THE INTIAL CONDITION OF THE FOR LOOP IS SUPPOSED TO BE OF THE SAME TYPE AS LOOP VARIABLE\n");
            printf ("\n");
         }

         if(Expression(Child(T,1)) != Expression(Child(T,3))){
            ErrorHeader(T);
            printf ("THE FINAL CONDITION OF THE FOR LOOP IS SUPPOSED TO BE OF THE SAME TYPE AS LOOP VARIABLE\n");
            printf ("\n");
         }
         ProcessNode(Child(T,4));
         while(NodeName(Temp) != ProgramNode){
            if(NodeName(Child(Child(Temp,1),1)) == NodeName(Child(Child(T,1),1))){
               ErrorHeader(T);
               printf ("NO FOR LOOP CAN REUSE THE LOOP VARIABLE OF A PARENT FOR LOOP\n");
               printf ("\n");
            }
            Temp = Decoration(Temp);
         }
         CloseScope();  printf("39 done\n");
         break;

      case CaseNode :   printf("40\n");
         Type1 = Expression(Child(T,1));
         if(NodeName(Child(T,NKids(T))) == OtherwiseNode){
            otrws = true;
            nn = NKids(T) - 1;
            ProcessNode(Child(Child(T,NKids(T)),1));
         }
         else{
            otrws = false;
            nn = NKids(T);
         }
         

         for(i=2;i<=nn;i++){
            if(NodeName(Child(Child(T,i),1)) == RangeClauseNode){
               if(Expression(Child(Child(Child(T,i),1),1)) != Type1 || Expression(Child(Child(Child(T,i),1),2)) != Type1){
                  ErrorHeader(T);
                  printf ("CASE CLAUSE SHOULD TYPE MATCH WITH THE CASE VARIABLE\n");
                  printf ("\n");
               }
            }
            else{
               if(Type1 != Expression(Child(Child(T,i),1))){
                  ErrorHeader(T);
                  printf ("DCASE CLAUSE SHOULD TYPE MATCH WITH THE CASE VARIABLE\n");
                  printf ("\n");
               }
            }

            ProcessNode(Child(Child(T,i),2));
         }
         printf("40 done\n");
         break;

      case NullNode : printf("41\n");  printf("41 done\n");
         break;

      case SubprogsNode : printf("65\n");
         for(Kid = 1;Kid<=NKids(T);Kid++){
            ProcessNode(Child(T,Kid));
         }  printf("65 done\n");
         break;

      case FcnNode : printf("66\n");
         Name1 = NodeName(Child(Child(T,1),1));
         Name2 = NodeName(Child(Child(T,NKids(T)),1));

         if (Name1 != Name2)
         {
           ErrorHeader(T);
           printf ("FUNCTION NAMES DO NOT MATCH\n");
           printf ("\n");
         }
         DTEnter(Name1,Child(T,1),T);
         OpenScope();
         DTEnter(S_CTXT,T,T);
         Type1 = Expression(Child(T,3));
         Decorate(Child(T,1),Type1);
         Decorate(Child(Child(T,1),1),T);
         ProcessNode(Child(T,2));
         for(Kid = 4;Kid <= NKids(T) -1; Kid++){
            ProcessNode(Child(T,Kid));
         }
         CloseScope();  printf("66 done\n");
         break;

      case ProcedureNode : printf("67\n");
         Name1 = NodeName(Child(Child(T,1),1));
         Name2 = NodeName(Child(Child(T,NKids(T)),1));

         if (Name1 != Name2)
         {
           ErrorHeader(T);
           printf ("FUNCTION NAMES DO NOT MATCH\n");
           printf ("\n");
         }
         DTEnter(Name1,Child(T,1),T);
         OpenScope();
         DTEnter(S_CTXT,T,T);
         Decorate(Child(T,1),TypeString);
         Decorate(Child(Child(T,1),1),T);
         ProcessNode(Child(T,2));
         for(Kid = 3;Kid <= NKids(T) -1; Kid++){
            ProcessNode(Child(T,Kid));
         }
         CloseScope();  printf("67 done\n");
         break;

      case CallNode :   printf("68\n");
         Type1 = Expression(Child(T,1));
         Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
         if(Mode != ProcedureNode){
            ErrorHeader(T);
            printf ("FUNCTION CALL AS A STATEMENT CANNOT HAVE ANYTHING OTHER THAN A PROCEDURE MODE\n");
            printf ("\n");
         }
         Temp = Decoration(Child(T,1));
         Temp = Child(Decoration(Child(Temp,1)),2);
         N = 0;
         for(Kid = 1;Kid<=NKids(Temp);Kid++){
            N = N + NKids(Child(Temp,Kid)) - 1;
         }
         if(N != (NKids(T) -1) ){
            ErrorHeader(T);
            printf ("NUMBER OF PARAMETERS DO NOT MATCH\n");
            printf ("\n");
         }
         else{
            /*here the type checking for each parameter is supposed to be done*/

            for(Kid = 2;Kid<=NKids(T);Kid++){
               Type2 = Expression(Child(T,Kid));
               N = 1;
               for(Kid1 = 1;Kid1<=NKids(Temp);Kid1++){
                  for(Kid2 = 1;Kid2<=NKids(Child(Temp,Kid1));Kid2++){
                     if(N == Kid -1){
                        Type3 = Decoration(Child(Child(Temp,Kid1),Kid2));
                        N = -1;
                        break;
                     }
                     N++;
                  }
                  if(N = -1){
                     break;
                  }
               }
               if(Type2 != Type3){
                  ErrorHeader(T);
                  printf ("PARAMETER TYPES DO NOT MATCH\n");
                  printf ("\n");
               }
            }
         }  printf("68 done\n");
         break;

      case ReturnNode : printf("69\n");
         Type1 = Expression(Child(T,1));
         Temp = Lookup(S_CTXT,T);
         if(NodeName(Temp) != FcnNode){
            ErrorHeader(T);
            printf ("RETURN USED OUTSIDE THE FUNCTION\n");
            printf ("\n");
         }
         Type2 = Decoration(Child(Temp,1));
         if(Type1 != Type2){
            ErrorHeader(T);
            printf ("RETURN TYPE DOES NOT MATCH\n");
            printf ("\n");
         }  printf("69 done\n");
         break;

      case ParamsNode : printf("70\n");
         for(Kid = 1;Kid <= NKids(T);Kid++){
            ProcessNode(Child(T,Kid));
         }  printf("70 done\n");
         break;

      default :
         ErrorHeader(T);
         printf ("UNKNOWN NODE NAME ");
         Write_String (stdout,NodeName(T));
         printf ("\n");

   }  /* end switch */
}  /* end ProcessNode */


void ModeFunction (TreeNode T){
   int Kid,Kid1,Kid2, N, i,nn;
   String Name1, Name2, Mode;
   TreeNode Type1, Type2, Type3,Temp;
   boolean otrws;

   switch (NodeName(T))
   {
      case LENode :    
      case EQNode : 
      case NENode : 
      case GENode : 
      case LTNode :  
      case GTNode : 
      case MulNode :
      case DivideNode : 
      case ModNode :
      case PowerNode :  printf("42\n");
         Name1 = NodeName(Child(T,1));
         Name2 = NodeName(Child(T,2));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF INTEGER FUNCTIONS MUST NOT BE OF MODE TYPE OR LIT TYPE\n");
               printf ("\n");
            }
         }

         if(Name2 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF INTEGER OPERATORS MUST NOT BE OF MODE TYPE OR LIT TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));
         ModeFunction(Child(T,2));  printf("42 done\n");
         break; 

      case OrNode : 
      case AndNode : printf("43\n");
         Name1 = NodeName(Child(T,1));
         Name2 = NodeName(Child(T,2));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF LOGICAL OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }

         if(Name2 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF LOGICAL OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));
         ModeFunction(Child(T,2));  printf("43 done\n");
         break;

      case PlusNode :
      case MinusNode :  printf("44\n");
         if(Rank(T) == 2){
            Name1 = NodeName(Child(T,1));
            Name2 = NodeName(Child(T,2));

            if(Name1 == IdentifierNode){
               Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
               if(Mode == TypeNode){
                  ErrorHeader(Child(T,1));
                  printf ("ARGUMENTS OF INTEGER OPERATORS MUST NOT BE OF MODE TYPE\n");
                  printf ("\n");
               }
            }

            if(Name2 == IdentifierNode){
               Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
               if(Mode == TypeNode){
                  ErrorHeader(Child(T,1));
                  printf ("ARGUMENTS OF INTEGER OPERATORS MUST NOT BE OF MODE TYPE\n");
                  printf ("\n");
               }
            }
            ModeFunction(Child(T,1));
            ModeFunction(Child(T,2));
         }
         else{
            Name1 = NodeName(Child(T,1));

            if(Name1 == IdentifierNode){
               Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
               if(Mode == TypeNode){
                  ErrorHeader(Child(T,1));
                  printf ("ARGUMENTS OF INTEGER OPERATORS MUST NOT BE OF MODE TYPE\n");
                  printf ("\n");
               }
            }
            ModeFunction(Child(T,1));
         }  printf("44 done\n");
         break;

      case NotNode : printf("45\n");
         Name1 = NodeName(Child(T,1));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF LOGICAL OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));  printf("45 done\n");
         break;

      case ReadNode :   printf("46\n");
         for (Kid = 2; Kid <= NKids(T)-1; Kid++){
            Name1 = NodeName(Child(Child(T,Kid),1));
            Mode = NodeName(Decoration(Child(Decoration(Child(Child(T,Kid),1)),1)));
            if(Mode != VarNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF INPUT CAN ONLY BE VAR MODE\n");
               printf ("\n");
            }
         }  printf("46 done\n"); 
         break;

      case IntegerNode : 
      case CharNode :
      case StringNode :
      case IdentifierNode :
      case EofNode : printf("47\n");   printf("47 done\n");
         break;

      case SuccNode :
      case PredNode :
      case OrdNode :
      case ChrNode : printf("48\n");
         Name1 = NodeName(Child(T,1));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF SUCC, PRED, CHR AND ORDS OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));  printf("48 done\n");
         break;

      case ProgramNode :   printf("49\n"); 
         for (Kid = 2; Kid <= NKids(T)-1; Kid++)
            ModeFunction(Child(T,Kid));
         printf("49 done\n"); break;

      case TypesNode :  
      case TypeNode :
      case LitNode: 
      case ConstsNode :
      case DclnsNode :  printf("50\n");   printf("50 done\n");
         break;

      case VarNode : printf("51\n");
         Name1 = NodeName(Child(T,NKids(T)));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,NKids(T))),1)));
            if(Mode != TypeNode){
               ErrorHeader(Child(T,1));
               printf ("TYPE FIELD IN THE DECLARAITION SHOULD ONLY BE OF MODE TYPE\n");
               printf ("\n");
            }
         }  printf("51 done\n");
         break;

      case ConstNode :  printf("52\n");
         Name1 = NodeName(Child(T,2));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode || Mode == VarNode){
               ErrorHeader(Child(T,1));
               printf ("CONSTANT DECLARATION SHOULD ONLY BE ASSIGNED MODE CONST OR LIT\n");
               printf ("\n");
            }
         }  printf("52 done\n");
         break;

      case BlockNode :  printf("53\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
               ModeFunction(Child(T,Kid));
         printf("53 done\n");break;

      case AssignNode : printf("54\n");
         Name1 = NodeName(Child(T,1));
         Name2 = NodeName(Child(T,2));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode != VarNode){
               ErrorHeader(Child(T,1));
               printf ("FIRST ARGUMENT OF ASSIGNMENT FUNCTION MUST BE OF MODE VAR\n");
               printf ("\n");
            }
         }

         if(Name2 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("SECOND ARGUMENT OF ASSIGNMENT FUNCTION MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));
         ModeFunction(Child(T,2));  printf("54 done\n");
         break;

      case SwapNode :   printf("55\n");
         Name1 = NodeName(Child(T,1));
         Name2 = NodeName(Child(T,2));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode != VarNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF SWAP FUNCTION MUST BE OF MODE VAR\n");
               printf ("\n");
            }
         }

         if(Name2 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
            if(Mode != VarNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF SWAP FUNCTION MUST BE OF MODE VAR\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));
         ModeFunction(Child(T,2));  printf("55 done\n");
         break;

      case OutputNode : printf("56\n");
         for (Kid = 1; Kid <= NKids(T); Kid++){
            ModeFunction(Child(Child(T,Kid),1));
         }  printf("56 done\n");
         break;

      case OutputTypeNode :   printf("57\n");
         Name1 = NodeName(Child(T,1));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF OUTPUT OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,1));  printf("57 done\n");
         break;

      case IfNode :
      case WhileNode :  printf("58\n");
         Name1 = NodeName(Child(T,1));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF WHILE AND IF OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,2));
         if(Rank(T) == 3){
            ModeFunction(Child(T,3));
         }  printf("58 done\n");
         break;

      case RepeatNode : printf("59\n");
         for (Kid = 1; Kid <= NKids(T) - 1; Kid++)
            ModeFunction(Child(T,Kid));

         Name1 = NodeName(Child(T,NKids(T)));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF REPEAT OPERATORS MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,NKids(T))); printf("59 done\n");
         break;

      case LoopNode :   printf("60\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
               ModeFunction(Child(T,Kid));
         printf("60 done\n");break;

      case ExitNode :   printf("61\n");   printf("61 done\n");
         break;
      case UptoNode :
      case DowntoNode:  printf("62\n");
         Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
         if(Mode != VarNode){
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF FOR OPERATORS MUST BE OF MODE VAR\n");
            printf ("\n");
         }

         Name1 = NodeName(Child(T,2));
         Name2 = NodeName(Child(T,3));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,2)),1)));
            if(Mode == TypeNode || Mode == ProcedureNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF FOR FUNCTIONS MUST NOT BE OF MODE TYPE OR PROCEDURE\n");
               printf ("\n");
            }
         }

         if(Name2 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,3)),1)));
            if(Mode == TypeNode || Mode == ProcedureNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF FOR OPERATORS MUST NOT BE OF MODE TYPE OR PROCEDURE\n");
               printf ("\n");
            }
         }
         ModeFunction(Child(T,2));
         ModeFunction(Child(T,3));
         ModeFunction(Child(T,4));  printf("62 done\n");
         break;

      case CaseNode :   printf("63\n");
         ModeFunction(Child(T,1));
         Name1 = NodeName(Child(T,1));

         if(Name1 == IdentifierNode){
            Mode = NodeName(Decoration(Child(Decoration(Child(T,1)),1)));
            if(Mode == TypeNode){
               ErrorHeader(Child(T,1));
               printf ("ARGUMENTS OF CASE OPERATOR MUST NOT BE OF MODE TYPE\n");
               printf ("\n");
            }
         }

         if(NodeName(Child(T,NKids(T))) == OtherwiseNode){
            otrws = true;
            nn = NKids(T) - 1;
            ModeFunction(Child(Child(T,NKids(T)),1));
         }
         else{
            otrws = false;
            nn = NKids(T);
         }
         

         for(i=2;i<=nn;i++){
            ModeFunction(Child(Child(T,i),2));
         }  printf("63 done\n");
         break;

      case NullNode :   printf("64\n");   printf("64 done\n");
         break;

      case SubprogsNode :  printf("73\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
               ModeFunction(Child(T,Kid));
         printf("73 done\n");break;

      case FcnNode : printf("74\n");
         ModeFunction(Child(T,2));
         Mode = NodeName(Decoration(Child(Decoration(Child(T,3)),1)));
         if(Mode != TypeNode){
            ErrorHeader(Child(T,1));
            printf ("ARGUMENTS OF CASE OPERATOR MUST NOT BE OF MODE TYPE\n");
            printf ("\n");
         }
         for (Kid = 4; Kid <= NKids(T)-1; Kid++)
               ModeFunction(Child(T,Kid));
         printf("74 done\n");break;

      case ProcedureNode : printf("75\n");
         ModeFunction(Child(T,2));
         for (Kid = 3; Kid <= NKids(T)-1; Kid++)
               ModeFunction(Child(T,Kid));
         printf("75 done\n");break;

      case CallNode :   printf("76\n");
         /*The mode of call cannot be checked here since there are two call types and each has a different mode
            So the checking happens at the ProcessNode and the Expression respectively*/
         for (Kid = 2; Kid <= NKids(T); Kid++)
               ModeFunction(Child(T,Kid));
         printf("76 done\n");break;

      case ReturnNode : printf("77\n");   printf("77 done\n");
         break;

      case ParamsNode : printf("78\n");
         for (Kid = 1; Kid <= NKids(T); Kid++)
               ModeFunction(Child(T,Kid));
         printf("78 done\n");break;

      default :
         ErrorHeader(T);
         printf ("UNKNOWN NODE NAME ");
         Write_String (stdout,NodeName(T));
         printf ("\n");

   }  /* end switch */
}
