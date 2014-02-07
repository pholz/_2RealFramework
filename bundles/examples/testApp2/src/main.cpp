#include "_2RealApplication.h"

using namespace _2Real;
using namespace _2Real::app;
using namespace std;

int main(int argc, char *argv[])
{
    Engine &testEngine = Engine::instance();
    testEngine.setBaseDirectory("../lib");

    BundleHandle testBundle = testEngine.loadBundle("libTestBundle");
    BlockHandle mult = testBundle.createBlockInstance("MultiplierBlock");
    mult.setUpdateRate(60.0);
    mult.setup();

    BlockHandle mult2 = testBundle.createBlockInstance("MultiplierBlock");
    mult2.setUpdateRate(60.0);
    mult2.setup();

    OutletHandle out = mult.getOutletHandle("Result");
    OutletHandle out2 = mult2.getOutletHandle("Result");

    mult.getInletHandle("NumberA").setValue<int>(5);
    mult.getInletHandle("NumberB").setValue<int>(3);

    mult2.getInletHandle("NumberA").link(out);
    mult2.getInletHandle("NumberB").setValue<int>(2);

    mult.start();
    mult2.start();

    while (true)
    {
        cout << "RESULT: " << out.getLastOutput().getData<int>() << " --> " <<
             out2.getLastOutput().getData<int>() << endl;
    }
}
