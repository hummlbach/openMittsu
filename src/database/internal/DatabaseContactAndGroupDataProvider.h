#ifndef OPENMITTSU_DATABASE_INTERNAL_DATABASECONTACTANDGROUPDATAPROVIDER_H_
#define OPENMITTSU_DATABASE_INTERNAL_DATABASECONTACTANDGROUPDATAPROVIDER_H_

#include "src/database/internal/DatabaseGroupMessageCursor.h"
#include "src/dataproviders/GroupDataProvider.h"

#include <QString>
#include <QVariant>

namespace openmittsu {
	namespace database {
		class Database;

		namespace internal {
			class InternalDatabaseInterface;

			class DatabaseContactAndGroupDataProvider : public openmittsu::dataproviders::GroupDataProvider {
				Q_OBJECT
			public:
				DatabaseContactAndGroupDataProvider(Database* signalSource, InternalDatabaseInterface* database);
				virtual ~DatabaseContactAndGroupDataProvider();

				// Groups
				virtual bool hasGroup(openmittsu::protocol::GroupId const& group) const override;
				virtual openmittsu::protocol::GroupStatus getGroupStatus(openmittsu::protocol::GroupId const& group) const override;
				virtual int getGroupCount() const override;
				virtual openmittsu::database::MediaFileItem getGroupImage(openmittsu::protocol::GroupId const& group) const override;
				virtual QSet<openmittsu::protocol::ContactId> getGroupMembers(openmittsu::protocol::GroupId const& group, bool excludeSelfContact) const override;
				virtual bool getGroupIsAwaitingSync(openmittsu::protocol::GroupId const& group) const override;

				virtual openmittsu::database::GroupData getGroupData(openmittsu::protocol::GroupId const& group, bool withDescription) const override;
				virtual QHash<openmittsu::protocol::GroupId, openmittsu::database::GroupData> getGroupDataAll(bool withDescription) const override;

				virtual void addGroup(QVector<NewGroupData> const& newGroupData) override;

				virtual void setGroupTitle(openmittsu::protocol::GroupId const& group, QString const& newTitle) override;
				virtual void setGroupImage(openmittsu::protocol::GroupId const& group, QByteArray const& newImage) override;
				virtual void setGroupMembers(openmittsu::protocol::GroupId const& group, QSet<openmittsu::protocol::ContactId> const& newMembers) override;

				virtual QSet<openmittsu::protocol::GroupId> getKnownGroups() const override;
				virtual QHash<openmittsu::protocol::GroupId, std::pair<QSet<openmittsu::protocol::ContactId>, QString>> getKnownGroupsWithMembersAndTitles() const override;
				virtual QHash<openmittsu::protocol::GroupId, QString> getKnownGroupsContainingMember(openmittsu::protocol::ContactId const& identity) const override;

				virtual std::shared_ptr<openmittsu::dataproviders::messages::GroupMessageCursor> getGroupMessageCursor(openmittsu::protocol::GroupId const& group) override;

				// Contacts
				virtual bool hasContact(openmittsu::protocol::ContactId const& contact) const override;

				virtual openmittsu::crypto::PublicKey getPublicKey(openmittsu::protocol::ContactId const& contact) const override;
				openmittsu::protocol::ContactStatus getContactStatus(openmittsu::protocol::ContactId const& contact) const;
				virtual int getContactCount() const override;
				
				virtual openmittsu::database::ContactData getContactData(openmittsu::protocol::ContactId const& contact, bool fetchMessageCount) const override;
				virtual QHash<openmittsu::protocol::ContactId, openmittsu::database::ContactData> getContactDataAll(bool fetchMessageCount) const override;

				virtual void addContact(QVector<NewContactData> const& newContactData) override;

				virtual void setFirstName(openmittsu::protocol::ContactId const& contact, QString const& firstName) override;
				virtual void setLastName(openmittsu::protocol::ContactId const& contact, QString const& lastName) override;
				virtual void setNickName(openmittsu::protocol::ContactId const& contact, QString const& nickname) override;
				virtual void setAccountStatus(openmittsu::protocol::ContactId const& contact, openmittsu::protocol::AccountStatus const& status) override;
				virtual void setVerificationStatus(openmittsu::protocol::ContactId const& contact, openmittsu::protocol::ContactIdVerificationStatus const& verificationStatus) override;
				virtual void setFeatureLevel(openmittsu::protocol::ContactId const& contact, openmittsu::protocol::FeatureLevel const& featureLevel) override;
				virtual void setColor(openmittsu::protocol::ContactId const& contact, int color) override;

				virtual void setAccountStatusBatch(QHash<openmittsu::protocol::ContactId, openmittsu::protocol::AccountStatus> const& status) override;
				virtual void setFeatureLevelBatch(QHash<openmittsu::protocol::ContactId, openmittsu::protocol::FeatureLevel> const& featureLevels) override;

				virtual std::shared_ptr<openmittsu::dataproviders::messages::ContactMessageCursor> getContactMessageCursor(openmittsu::protocol::ContactId const& contact) override;

				virtual QSet<openmittsu::protocol::ContactId> getKnownContacts() const override;
				virtual QSet<openmittsu::protocol::ContactId> getContactsRequiringFeatureLevelCheck(int maximalAgeInSeconds) const override;
				virtual QSet<openmittsu::protocol::ContactId> getContactsRequiringAccountStatusCheck(int maximalAgeInSeconds) const override;

				virtual QHash<openmittsu::protocol::ContactId, openmittsu::crypto::PublicKey> getKnownContactsWithPublicKeys() const override;
				virtual QHash<openmittsu::protocol::ContactId, QString> getKnownContactsWithNicknames(bool withSelfContactId) const override;
			private slots:
				void onGroupChanged(openmittsu::protocol::GroupId const& group);
				void onContactChanged(openmittsu::protocol::ContactId const& contact);
				void onContactStartedTyping(openmittsu::protocol::ContactId const& identity);
				void onContactStoppedTyping(openmittsu::protocol::ContactId const& identity);
				void onContactHasNewMessage(openmittsu::protocol::ContactId const& identity, QString const& messageUuid);
				void onGroupHasNewMessage(openmittsu::protocol::GroupId const& group, QString const& messageUuid);
			private:
				Database* const m_signalSource;
				InternalDatabaseInterface* const m_database;

				QVariant queryField(openmittsu::protocol::GroupId const& group, QString const& fieldName) const;

				void setFields(openmittsu::protocol::GroupId const& group, QVariantMap const& fieldsAndValues, bool doAnnounce = true);
				void setFields(openmittsu::protocol::ContactId const& contact, QVariantMap const& fieldsAndValues, bool doAnnounce = true);

				QVariant queryField(openmittsu::protocol::ContactId const& contact, QString const& fieldName) const;

				QString buildNickname(QString const& nickname, QString const& firstName, QString const& lastName, openmittsu::protocol::ContactId const& contact) const;
				QString getGroupDescription(QString const& memberField) const;
				QHash<openmittsu::protocol::ContactId, QString> getNicknames(QSet<openmittsu::protocol::ContactId> const& contacts) const;
			};
		}
	}
}

#endif // OPENMITTSU_DATABASE_INTERNAL_DATABASECONTACTANDGROUPDATAPROVIDER_H_
