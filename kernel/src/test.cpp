#include "_2RealContext.h"
#include "_2RealOutputContainer.h"

using namespace _2Real;

int main(int argc, char *argv[])
{

	//get _2Real context instance
	ContextPtr context = Context::instance();

	//request creation of new output container
	OutputContainerPtr config = context->newConfiguration();

	std::cout << "configuration container created" << std::endl;

	//begin configuration of new output container
	config->beginConfiguration();

	std::cout << "begin configuration" << std::endl;

	//add a sequence container
	config->beginSequence();

	std::cout << "sequence container created" << std::endl;

		//add a synchronization container
		config->beginSynchronization();

		std::cout << "synchronization container created" << std::endl;

			//add 1st service
			config->beginServiceConfiguration("RandomImage_ushort", "ImageProcessing");

			std::cout << "new user service created" << std::endl;
			
			config->configureSetupParameter<unsigned short>("image width", 400);
			config->configureSetupParameter<unsigned short>("image height", 400);
			const Variable img1 = config->configureOutputParameter("output image");
			
			std::cout << "service variables added to config" << std::endl;
			
			config->endServiceConfiguration();

			std::cout << "service configuration finished" << std::endl;

			/*
			//add 2nd service
			config->beginServiceConfiguration("RandomImage_ushort", "ImageProcessing");
			config->configureSetupParameter<unsigned short>("image width", 400);
			config->configureSetupParameter<unsigned short>("image height", 400);
			const Variable img2 = config->configureOutputParameter("output image");
			config->endServiceConfiguration();
			*/

		//end synch block
		config->endGroup();

		std::cout << "container configuration finished" << std::endl;

		/*
		config->beginServiceConfiguration("ImageAddition_ushort", "ImageProcessing");
		config->configureSetupParameter<unsigned short>("image width", 400);
		config->configureSetupParameter<unsigned short>("image height", 400);
		config->configureInputParameter("input image 1", img1);
		config->configureInputParameter("input image 2", img2);
		config->endServiceConfiguration();
		*/

	//end sequence
	config->endGroup();

	std::cout << "container configuration finished" << std::endl;

	if (!config->endConfiguration())
	{
		std::cout << "configuration failed" << std::endl;
	}
	else
	{
		std::cout << "container configuration finished" << std::endl;
	}

	Sleep(100000);
	
	return 0;
}