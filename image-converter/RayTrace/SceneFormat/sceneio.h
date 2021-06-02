#include "scene.pb.h"
#include <iostream>
#include <fstream>
#include <google/protobuf/util/json_util.h>

#ifndef SCENEFORMAT_SCENEIO_H
#define SCENEFORMAT_SCENEIO_H

namespace scene_format {
	class SceneIO {
	public:
		virtual scene_format::Scene read(std::string path) = 0;
		virtual void save(scene_format::Scene scene, std::string path) = 0;
		virtual void save_as_json(scene_format::Scene scene, std::string path) = 0;
	};

	class SceneFormatIO : virtual public SceneIO {
	public:
		std::string read_to_string(std::istream& in)
		{
			std::string ret;
			char buffer[4096];
			while (in.read(buffer, sizeof(buffer)))
				ret.append(buffer, sizeof(buffer));
			ret.append(buffer, in.gcount());
			return ret;
		}

		scene_format::Scene read(std::istream* istream) {
			scene_format::Scene scene;

			std::string contents = read_to_string(*istream);

			if (!scene.ParseFromString(contents)) {
				google::protobuf::util::JsonParseOptions options;
				JsonStringToMessage(contents, &scene, options);
			}

			return scene;
		}

		scene_format::Scene read(std::string path) {
			std::fstream input(path, std::ios::in | std::ios::binary);
			return read(&input);
		}

		void save(scene_format::Scene scene, std::ostream* ostream) {
			scene.SerializeToOstream(ostream);
		}

		void save(scene_format::Scene scene, std::string path) {
			std::ofstream output_file;
			output_file.open(path);
			save(scene, &output_file);
			output_file.close();
		}

		void save_as_json(scene_format::Scene scene, std::ostream* ostream) {
			std::string json_string;

			google::protobuf::util::JsonPrintOptions options;
			options.add_whitespace = true;
			options.preserve_proto_field_names = true;
			MessageToJsonString(scene, &json_string, options);

			*ostream << json_string;
		}

		void save_as_json(scene_format::Scene scene, std::string path) {
			std::ofstream output_file;
			output_file.open(path);
			save_as_json(scene, &output_file);
			output_file.close();
		}
	};
}

#endif //SCENEFORMAT_SCENEIO_H
