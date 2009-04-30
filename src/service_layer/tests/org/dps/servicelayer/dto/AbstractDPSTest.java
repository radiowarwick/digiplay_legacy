package org.dps.servicelayer.dto;

import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;


public abstract class AbstractDPSTest extends AbstractDependencyInjectionSpringContextTests
 {
		
	private Long rootFileID = Long.valueOf(0);
	private Long systemUserID = Long.valueOf(0);
	private Long testUserID = Long.valueOf(1);
	private Long testGroupID = Long.valueOf(1);
	protected HibernateTransactionManager txManager;
	
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	
	protected File getRootDir(Session session) {
		Query query = session.createQuery("from File where fileID=?");
		query.setLong(0, rootFileID.longValue());
		return (File) query.uniqueResult();
	}
	
	protected User getSystemUser(Session session) {
		Query query = session.createQuery("from User where userID=?");
		query.setLong(0, systemUserID.longValue());
		return (User) query.uniqueResult();
	}
	
	protected User getTestUser(Session session) {
		Query query = session.createQuery("from User where userID=?");
		query.setLong(0, testUserID.longValue());
		return (User) query.uniqueResult();
	}
	
	protected Group getTestGroup(Session session) {
		Query query = session.createQuery("from Group where groupID=?");
		query.setLong(0, testGroupID.longValue());
		return (Group) query.uniqueResult();
	}

	public void setRootFileID(Long rootFileID_) {
		rootFileID = rootFileID_;
	}

	public void setSystemUserID(Long systemUserID_) {
		systemUserID = systemUserID_;
	}

	public void setTestUserID(Long testUserID_) {
		testUserID = testUserID_;
	}

	public void setTestGroupID(Long testGroupID_) {
		testGroupID = testGroupID_;
	}

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}
}
