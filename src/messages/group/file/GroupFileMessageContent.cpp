#include "src/messages/group/file/GroupFileMessageContent.h"

#include "src/messages/MessageContentRegistry.h"
#include "src/protocol/GroupId.h"
#include "src/protocol/ProtocolSpecs.h"
#include "src/utility/Logging.h"

#include <memory>

namespace openmittsu {
	namespace messages {
		namespace group {

			// Register this MessageContent with the MessageContentRegistry
			bool GroupFileMessageContent::registrationResult = MessageContentRegistry::getInstance().registerContent(PROTO_MESSAGE_SIGNATURE_GROUP_FILE, std::make_shared<TypedMessageContentFactory<GroupFileMessageContent>>());


			GroupFileMessageContent::GroupFileMessageContent() : GroupMessageContent(openmittsu::protocol::GroupId(0, 0)) {
				// Only accessible and used by the MessageContentFactory.
			}

			GroupFileMessageContent::GroupFileMessageContent(openmittsu::protocol::GroupId const& groupId) : GroupMessageContent(groupId) {
				// Intentionally left empty.
			}

			GroupFileMessageContent::~GroupFileMessageContent() {
				// Intentionally left empty.
			}

			GroupMessageContent* GroupFileMessageContent::clone() const {
				return new GroupFileMessageContent(getGroupId());
			}

			MessageContent* GroupFileMessageContent::fromPacketPayload(FullMessageHeader const& messageHeader, QByteArray const& payload) const {
				LOGGER_DEBUG("Received Group File with payload {}", QString(payload.toHex()).toStdString());

				verifyPayloadMinSizeAndSignatureByte(PROTO_MESSAGE_SIGNATURE_GROUP_FILE, 1 + openmittsu::protocol::GroupId::getSizeOfGroupIdInBytes() + 1, payload);

				openmittsu::protocol::GroupId const groupId(openmittsu::protocol::GroupId::fromData(payload.mid(1, openmittsu::protocol::GroupId::getSizeOfGroupIdInBytes())));

				// TODO
				QByteArray const data = (payload.mid(1 + openmittsu::protocol::GroupId::getSizeOfGroupIdInBytes()));

				return new GroupFileMessageContent(groupId);
			}

			QByteArray GroupFileMessageContent::toPacketPayload() const {
				QByteArray result(1, PROTO_MESSAGE_SIGNATURE_GROUP_FILE);
				result.append(getGroupId().getGroupIdAsByteArray());

				// TODO

				return result;
			}

		}
	}
}
