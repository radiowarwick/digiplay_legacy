package org.dps.servicelayer.dto;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.test.context.TestExecutionListeners;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;
import static org.dps.servicelayer.dto.Constants.*;

public class CartsetTest extends AbstractDependencyInjectionSpringContextTests
 {
	
	final static Logger LOGGER = LoggerFactory.getLogger(CartsetTest.class);
	
	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	private HibernateTransactionManager txManager;
	
	public HibernateTransactionManager getTxManager() {
		return txManager;
	}

	public void setTxManager(HibernateTransactionManager txManager_) {
		txManager = txManager_;
	}

	
	@SuppressWarnings("unchecked")
	@Test
	public void testShallowRetrieve() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=20");
			List<Cartset> cList = (List<Cartset>) query.list();
					
			assertNotNull(cList);
			assertEquals("More than one result returned",1, cList.size());
			Cartset cartset = cList.get(0);
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(20), cartset.getFileID());
			assertEquals("Phils Cartwall", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
	@SuppressWarnings("unchecked")
	@Test
	public void testDeepRetrieve() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=20");
			List<Cartset> cList = (List<Cartset>) query.list();
					
			assertNotNull(cList);
			assertEquals("More than one result returned",1, cList.size());
			Cartset cartset = cList.get(0);
			LOGGER.debug(cartset.toString());
			assertNotNull(cartset.getCartwalls());
			assertEquals("Invalid number of cartwalls returned",2, cartset.getCartwalls().size());
			Cartwall cartwall = cartset.getCartwalls().get(0);
			assertEquals("WALL 1",cartwall.getName());
			assertEquals(Integer.valueOf(1),cartwall.getPage());
			assertEquals("FIRST WALL", cartwall.getDescription());
			assertEquals(cartset, cartwall.getCartset());
			assertNotNull(cartwall.getCarts());
			assertEquals("Invalid number of carts returned",2, cartwall.getCarts().size());
			CartAudio cart = null;
			for(CartAudio temp : cartwall.getCarts()) {
				if(temp.getCartID() != null && temp.getCartID().equals(Integer.valueOf(1))) {
					cart = temp;
				}
			}
			assertNotNull(cart);
			assertEquals("CART 1", cart.getText());
			assertEquals(cartwall, cart.getCartwall());
			assertNotNull(cart.getAudio());
			assertEquals(Long.valueOf(1), cart.getAudio().getFileID());
			assertNotNull(cart.getStyle());
			CartStyle style = cart.getStyle();
			assertEquals("PLAIN",style.getName());
			assertEquals("DEFAULT",style.getDescription());
			assertNotNull(style.getProperties());
			assertEquals(2, style.getProperties().size());
			CartStyleProperty prop = style.getProperties().get("TEXT");
			assertNotNull(prop);
			assertEquals("#000000", prop.getValue());
			assertEquals(style, prop.getStyle());
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}


	@Test
	public void testSimpleInsert() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Long fileID = null;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from File where fileID=0");
			File root = (File) query.uniqueResult();
			
			Cartset cartset = new Cartset();
			cartset.setAllExecute(Boolean.FALSE);
			cartset.setAllRead(Boolean.FALSE);
			cartset.setAllWrite(Boolean.FALSE);
			cartset.setDescription("Test Cartset");
			cartset.setEntityType(FILE_TYPE_CARTSET); //TODO Maybe remove
			cartset.setFilename("Test Cartset");
			cartset.setName("Test Cartset name");
			cartset.setGroupExecute(Boolean.TRUE);
			cartset.setGroupRead(Boolean.TRUE);
			cartset.setGroupWrite(Boolean.FALSE);
			cartset.setGroupID(-1); //TODO replace with group
			cartset.setOwnerID(-1); //TODO: replace with user
			cartset.setParent(root);
			cartset.setUserExecute(Boolean.TRUE);
			cartset.setUserRead(Boolean.TRUE);
			cartset.setUserWrite(Boolean.TRUE);
			session.save(cartset);
			
			assertNotNull(cartset.getFileID());
			fileID = cartset.getFileID();
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=" + fileID.toString());
			List<Cartset> cList = (List<Cartset>) query.list();
					
			assertNotNull(cList);
			assertEquals("More than one result returned",1, cList.size());
			Cartset cartset = cList.get(0);
			LOGGER.debug(cartset.toString());
			assertEquals(fileID, cartset.getFileID());
			assertEquals("Test Cartset name", cartset.getName());
			assertEquals("Test Cartset", cartset.getFilename());
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
}
