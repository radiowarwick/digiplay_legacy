package org.dps.servicelayer;

import org.dps.servicelayer.auth.IFileAuthoriser;
import org.dps.servicelayer.auth.IUserContext;
import org.dps.servicelayer.dto.File;
import org.dps.servicelayer.dto.Group;
import org.dps.servicelayer.dto.User;
import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.beans.factory.annotation.Required;
import org.springframework.orm.hibernate3.HibernateTransactionManager;

public abstract class AbstractService {
	protected HibernateTransactionManager txManager;
	protected IFileAuthoriser authoriser;
	protected IUserContext userContext;
	
	protected File getFile(Session session, Long fileID) {
		Query query = session.createQuery("from File where fileID=?");
		query.setLong(0, fileID);
		return (File) query.uniqueResult();
	}
	
	protected User getUser(Session session, Long useriD) {
		Query query = session.createQuery("from User where userID=?");
		query.setLong(0, useriD);
		return (User) query.uniqueResult();
	}
	
	protected Group getGroup(Session session, Long groupID) {
		Query query = session.createQuery("from Group where groupID=?");
		query.setLong(0, groupID);
		return (Group) query.uniqueResult();
	}
	
	@Required
	public HibernateTransactionManager getTxManager() {
		return txManager;
	}

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}

	public IFileAuthoriser getAuthoriser() {
		return authoriser;
	}

	public void setAuthoriser(IFileAuthoriser authoriser_) {
		authoriser = authoriser_;
	}

	public IUserContext getUserContext() {
		return userContext;
	}

	public void setUserContext(IUserContext userContext_) {
		userContext = userContext_;
	}
}
