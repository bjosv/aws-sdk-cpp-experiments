#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentialsProvider.h>

using Aws::S3::S3Client;

static const char* ALLOCATION_TAG = "Client_Init_Cleanup";

int main() {
    Aws::SDKOptions options;

    /* See: https://awslabs.github.io/aws-crt-cpp/class_aws_1_1_crt_1_1_io_1_1_event_loop_group.html */
    options.ioOptions.clientBootstrap_create_fn = []() {
        Aws::Crt::Io::EventLoopGroup eventLoopGroup(1); /* threadCount = 1 */
        Aws::Crt::Io::DefaultHostResolver defaultHostResolver(eventLoopGroup, 8, 30);
        auto clientBootstrap = Aws::MakeShared<Aws::Crt::Io::ClientBootstrap>(ALLOCATION_TAG, eventLoopGroup, defaultHostResolver);
        clientBootstrap->EnableBlockingShutdown();
        return clientBootstrap;
    };

    Aws::InitAPI(options);
    {
        Aws::Client::ClientConfiguration cfg;
        cfg.maxConnections = 1;
        cfg.verifySSL = true;

        S3Client* client = new S3Client(Aws::Auth::AWSCredentials("minioadmin", "minioadmin"), cfg,
                                        Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

        /* Get info
           VmSize - virtual (total program size)
           VmPeak - virtual (peak)
           VmRSS  - resident memory usage
           VmHWM  - resident memory usage (peak)
        */
        FILE* status = fopen("/proc/self/status", "r");
        char line[1024];
        while(fgets(line, sizeof(line), status) ) {
            printf("%s", line);
        }
    }
    Aws::ShutdownAPI(options);
}
