/*
 * Client example taken from:
 * https://github.com/minio/minio/issues/10176#issuecomment-667765704
 */

#include <iostream>
#include <fstream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/Bucket.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/s3/model/PutObjectRequest.h>

using Aws::S3::S3Client;
using Aws::S3::Model::PutObjectRequest;

std::string BucketName = "mybucket";
std::string objectKey = "mykey";
std::string pathkey = "/tmp/mydata.dat";

int main() {
    Aws::SDKOptions m_options;
    S3Client* m_client = { NULL };

    Aws::InitAPI(m_options);
    Aws::Client::ClientConfiguration cfg;
    cfg.endpointOverride = "127.0.0.1:9000";
    cfg.scheme = Aws::Http::Scheme::HTTP;
    cfg.verifySSL = false;
    //Aws::Auth::AWSCredentials cred("xxxxxxx", "xxxxxxxxx");
    m_client = new S3Client(Aws::Auth::AWSCredentials("minioadmin", "minioadmin"), cfg,
                            Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Never, false);

    PutObjectRequest putObjectRequest;
    putObjectRequest.WithBucket(BucketName.c_str()).WithKey(objectKey.c_str());
    auto input_data = Aws::MakeShared<Aws::FStream>("PutObjectInputStream", pathkey.c_str(), std::ios_base::in | std::ios_base::binary);
    putObjectRequest.SetBody(input_data);
    auto putObjectResult = m_client->PutObject(putObjectRequest);
    if (putObjectResult.IsSuccess())
    {
        std::cout << "Done!" << std::endl;
        delete m_client;                                // PATCHED: need when built with: -DUSE_CRT_HTTP_CLIENT=ON
        return true;
    }
    else
    {
        std::cout << "PutObject error: " <<
            putObjectResult.GetError().GetExceptionName() << " " <<
            putObjectResult.GetError().GetMessage() << std::endl;
        return false;
    }
}
