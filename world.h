#include <iostream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <set>
#include "random.h"
#include "HTTPRequest.h"
using namespace javarand;


struct coords
{
  int x;
  int z;
};

bool operator<(const coords& c1, const coords& c2)
{
  return c1.x < c2.x;
}

bool operator==(const coords& c1, const coords& c2)
{
  return c1.x == c2.x;
}

namespace world
{
  class World
  {
    private:
      long seed;
      bool logging = false;
      bool returnOnlyRectangles = true;
      int spacing = 1;
      int min_size = 8;
      JavaRandom rand;

      void search(int radius);
      coords findLargestRect(std::vector<int>);
      bool isSlimeChunk(int x, int z);
      void getCluster(int x, int z, int depth = 0);
      std::set<std::vector<coords>> slime_clusters;
      coords createSubMatrixHistogram(std::vector<std::vector<bool>> chunks);
      std::vector<std::vector<bool>> generateClusterRegion(std::vector<coords>);

    public:
      void printMap(int radius);
      void printCluster(std::vector<coords> chunks);

      World(long seed, int radius, int min_size, int spacing, bool logging, bool returnOnlyRectangles) {
        this->min_size = min_size;
        this->returnOnlyRectangles = returnOnlyRectangles;
        this->logging = logging;
        this->spacing = spacing;
        this->seed = seed;
        this->search(radius);
      }
  };

  // Determine if there is a slime chunk at x, z
  bool World::isSlimeChunk(int x, int z) 
  {
    // Set seed and location
    rand.setSeed(
      this->seed +
      (int) (x * x * 0x4c1906) +
      (int) (x * 0x5ac0db) +
      (int) (z * z) * 0x4307a7L +
      (int) (z * 0x5f24f) ^ 0x3ad8025fL);

    // Determine if slime chunk
    return !(rand.nextInt(10));
  }

  // Search radius around 0, 0 for slime chunks
  void World::search(int radius)
  {
    int half_radius = radius / 2;
    for (int z = -half_radius; z < half_radius; z+=this->spacing)
      for (int x = -half_radius; x < half_radius; x+=this->spacing)
        getCluster(x, z, 1);
  }

  // https://www.youtube.com/watch?v=g8bSdXCG-lA
  coords World::createSubMatrixHistogram(std::vector<std::vector<bool>> chunks)
  {
    // Initialize array and set all values to 0
    std::vector<int> histogram(chunks[0].size(), 0);
    coords maxDimensions{0, 0};

    // increment each element if multiple y chunks ( like histogram values )
    for (int x = 0; x < chunks.size(); x++)
    {
      for (int z = 0; z < chunks[0].size(); z++)
      {
        // If slime chunk
        if (chunks[x][z])
          histogram[z]++;
        else
          histogram[z]=0;
      }
      
      // Find largest rectangle in region cluster
      coords temp = this->findLargestRect(histogram);
      if (temp.x * temp.z > maxDimensions.x * maxDimensions.z) maxDimensions = temp;
    }

    return maxDimensions;
  }

  // Find largest rect in submatrix histogram and return dimensions
  coords World::findLargestRect(std::vector<int> histogram)
  {
    int h;
    int i;
    int tempH;
    int tempPos = 0;
    int tempSize;
    coords dimensions;
    double maxSize = -std::numeric_limits<double>::infinity();
    std::stack<int> pStack;
    std::stack<int> hStack;

    for (i = 0; i < histogram.size(); i++)
    {
      h = histogram[i];

      if (!hStack.size() || h > hStack.top()) {
        hStack.push(h);
        pStack.push(i);
      } else if (h < hStack.top()) {
        while (!hStack.empty() && h < hStack.top()) {
          tempH = hStack.top();
          tempPos = pStack.top();
          hStack.pop();
          pStack.pop();
          tempSize = tempH * (i - tempPos);
          maxSize = std::max((double)tempSize, maxSize);
          if (maxSize == tempSize) dimensions = coords{i - tempPos, tempH};
        }
        hStack.emplace(h);
        pStack.emplace(tempPos);
      }
    }

    while (!hStack.empty()) {
      tempH = hStack.top();
      tempPos = pStack.top();
      hStack.pop();
      pStack.pop();
      tempSize = tempH * (i - tempPos);
      maxSize = std::max((double)tempSize, maxSize);
      if (maxSize == tempSize) dimensions = coords{i - tempPos, tempH};
    }
    return dimensions;
  }

  // Recursively search for nearby slime chunks within cluster and return dimensions
  void World::getCluster(int x, int z, int depth)
  {
    // Holds coordinates of already checked chunks 
    static std::vector<coords> checked_chunks;
    coords current_coords = coords{x, z};
    
    // If not slime chunk and checked_chunks does not include these coordinates ( chunk hasn't been checked ), return false;
    bool contains_chunk = std::any_of(checked_chunks.begin(), checked_chunks.end(), [current_coords](coords c1){ return(c1.x == current_coords.x && c1.z == current_coords.z);});
    if (this->isSlimeChunk(x, z) && !contains_chunk) {

      // If initial cluster check, clear checked_chunks
      if (depth)
        checked_chunks.clear();

      // Push self to checked chunks
      checked_chunks.push_back(current_coords);

      // Check sides
      getCluster(x+1, z);
      getCluster(x-1, z);
      getCluster(x, z+1);
      getCluster(x, z-1);


      // Add cluster to set if size >= min_size
      if (checked_chunks.size() >= this->min_size && depth) {

        // Sort cluster array to prevent duplicates
        std::stable_sort(checked_chunks.begin(), checked_chunks.end());
        auto it_res = this->slime_clusters.insert(checked_chunks);

        // Find largest rect dimensions within cluster region
        std::vector<std::vector<bool>> cluster_region = this->generateClusterRegion(checked_chunks);
        coords largest_rect_dimensions = this->createSubMatrixHistogram(cluster_region);

        // If should return cluster
        bool should_return_cluster = (this->returnOnlyRectangles ? largest_rect_dimensions.x * largest_rect_dimensions.z > this->min_size : checked_chunks.size() > this->min_size);

        // Only call if not duplicate
        if (it_res.second && this->logging && should_return_cluster) {
          std::cout << "Seed: " << this->seed << std::endl;
          std::cout << "Chunks: (" << x << ", " << z << ")" << std::endl;
          std::cout << "Coordinates: (" << x*16 << ", " << z*16 << ")" << std::endl;

          if (this->returnOnlyRectangles) {
            std::cout << "Size: " << largest_rect_dimensions.x * largest_rect_dimensions.z << std::endl;
          } else {
            std::cout << "Size: " << checked_chunks.size() << std::endl;
          }

          this->printCluster(checked_chunks);
          std::cout << "-----------------------------------------------" << std::endl;

          // Return cluster if area >= this->min_size
          if (largest_rect_dimensions.x * largest_rect_dimensions.z >= this->min_size) {
            // Post to database
            try
            {
              http::Request request("http://149.28.75.54/api");
              std::string chunks_string;
              std::string params;

              // Convert vector of coords to vector of strings
              for(coords c : checked_chunks)
                chunks_string = chunks_string + "{\"x\": " + std::to_string(c.x) + ", \"z\": " + std::to_string(c.z) + "}, ";

              // Trim end of string
              chunks_string = chunks_string.substr(0, chunks_string.length()-2);
              chunks_string = "[" + chunks_string + "]";

              params = params +
                "{\"seed\": " + std::to_string(this->seed) +
                " ,\"chunks\": " + chunks_string +
                " ,\"coords\": " + "{\"x\": " + std::to_string(checked_chunks[0].x << 4) + ", \"z\": " + std::to_string(checked_chunks[0].z << 4) + "}" + 
                " ,\"size\": " + std::to_string(checked_chunks.size()) +
                "}";

              std::cout << params;


              // Send request
              const auto response = request.send("POST", params, {
                  "Content-Type: application/json"
              });
              std::cout << std::string{response.body.begin(), response.body.end()} << '\n'; // print the result

            }
            catch (const std::exception& e)
            {
              std::cerr << "Request failed, error: " << e.what() << '\n';
            }
          }
        }
      }
    }
  }

  // Generate 2D array representation of cluster
  std::vector<std::vector<bool>> World::generateClusterRegion(std::vector<coords> chunks)
  {
    // Initialize bounding box
    int top = chunks.front().x;
    int bottom = top;
    int left = chunks.front().z;
    int right = left;

    // Find bounding box
    for (coords &c : chunks) {
      left = std::min(c.z, left);
      right = std::max(c.z, right);
      top = std::max(c.x, top);
      bottom = std::min(c.x, bottom);
    }

    // Bounding box dimensions
    int width = right + 1 - left;
    int height = top + 1 - bottom;

    // Create 2D array representation of chunk cluster
    std::vector<std::vector<bool>> cluster(width, std::vector<bool>(height, 0));

    // Set cluster 
    for (int z = 0; z < width; z++)
    {
      for (int x = 0; x < height; x++)
      {
        coords c{x+bottom, z+left};
        bool chunks_contains = std::any_of(chunks.begin(), chunks.end(), [c](coords c1){ return(c1.x == c.x && c1.z == c.z);});
        cluster[z][x] = chunks_contains;
      }
    }
    return cluster;
  }

  // Display chunk cluster
  void World::printCluster(std::vector<coords> chunks)
  {
    std::vector<std::vector<bool>> cluster = this->generateClusterRegion(chunks);

    // Display cluster
    for (int i = 0; i < cluster.size(); i++) 
    {
      for (int j = 0; j < cluster[0].size(); j++) 
      {
        std::cout << (cluster[i][j] ? "■ " : "□ ");
      }
      std::cout << std::endl;
    }
  }


  // Print map to console
  void World::printMap(int radius)
  {
    int half_radius = radius / 2;
    for (int z = -half_radius; z < half_radius; z+=this->spacing)
    {
      for (int x = -half_radius; x <= half_radius; x+=this->spacing)
      {
         if (z == -half_radius) {
          // Print x coordinates
          std::cout << (x >= 0 ? " " : "") << x << " ";
        } else {
          // Display chunk type
          std::cout << (isSlimeChunk(x, z) ? "■ " : "□ ");
        }
      }
      std::cout << std::endl;
    }

    for (int z = -half_radius; z < half_radius; z++)
      std::cout << z << " ";
  }
};

