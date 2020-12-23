/*The ~/Registry.CC file is CosmiC code.
You can execute a tree branch of it.  The Zenith
branch is executed in the Zenith task boot phase.
Normally, you will place var declarations
in the branch you make, but since an arthmetic expression
is valid in CosmiC you can place simple expressions
without vars.
*/

RegDefault("DemoCompany/Game1", "F64 best_score=1.23;\n");
RegDefault("DemoCompany/Game1/SimpleVal", "1234;\n");
RegExe("DemoCompany/Game1");

U0 Game()
{
	I64 i = RegExe("DemoCompany/Game1/SimpleVal");

	"High Score:%6.5f\n", best_score;
	"Val:%d\n", i;
	i++;
	best_score = tS;
//You could combine these into one write by making
	//the $$TR...$$ and $$ID,2$$, $$ID,-2$$, cmds yourself.
	RegWrite("DemoCompany/Game1", "F64 best_score=%9.5f;\n", best_score);
	RegWrite("DemoCompany/Game1/SimpleVal", "%d;\n", i);
}

Game;
