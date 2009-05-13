package org.dps.servicelayer.cartset;

import java.util.List;

import org.dps.servicelayer.AbstractService;
import org.dps.servicelayer.dto.Cartset;
import org.dps.servicelayer.dto.CartsetSummary;
import org.dps.servicelayer.dto.Cartwall;
import org.dps.servicelayer.dto.File;
import org.dps.servicelayer.dto.Group;
import org.dps.servicelayer.dto.User;
import org.hibernate.Query;
import org.hibernate.Session;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class CartsetService extends AbstractService implements ICartsetService, InitializingBean {
	
	public CartsetResponse getCartset(CartsetRequest params_) {
		CartsetResponse response = new CartsetResponse();
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, params_.getCartsetID());
			
			Cartset cartset = (Cartset) query.uniqueResult();
			PermissionedCartset pc = authoriser.getFileAuthorisation(cartset, new PermissionedCartset());
			if(pc.isRead()) {
				response.setPermissionedCartset(pc);
				//This ensures that we don't have any stale collections 
				pc.getItem().makeSafe();
			}
		} catch (Exception e) {
			ts.setRollbackOnly();
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return response;
	}
	
	@SuppressWarnings("unchecked")
	public CartsetsResponse getCartsets(CartsetsRequest params_) {
		CartsetsResponse response = new CartsetsResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset");
			for(Cartset cartset : (List<Cartset>)query.list()) {
				CartsetSummary summary = new CartsetSummary(cartset);
				PermissionedCartsetSummary permSummary = authoriser.getFileAuthorisation(summary, new PermissionedCartsetSummary());
				if(permSummary.isRead()) {
					response.addPermissionedCartsetSummary(permSummary);
				}
			}
			response.getResultSetDetails().setNumPages(1);
			response.getResultSetDetails().setPageNum(0);
			response.getResultSetDetails().setNumResults(query.list().size());
		} catch (Exception e) {
			ts.setRollbackOnly();
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return response;
	}
	
	@Override
	public AddCartsetResponse addCartset(AddCartsetRequest params_) {
		AddCartsetResponse response = new AddCartsetResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			
			
			File parent = this.getFile(session, params_.getParentID());
			User owner = this.getUser(session, userContext.currentUserID());
			Group group = null;
			if(params_.getGroupID() != null) {
				this.getGroup(session, params_.getGroupID());
			}
			
			Cartset newCartset = new Cartset();
			newCartset.setAllExecute(params_.getAllExecute());
			newCartset.setAllRead(params_.getAllRead());
			newCartset.setAllWrite(params_.getAllWrite());
			newCartset.setDescription(params_.getDescription());
			if(params_.getFilename() != null) { 
				newCartset.setFilename(params_.getFilename());
			} else {
				newCartset.setFilename(params_.getName());
			}
			newCartset.setGroupExecute(params_.getGroupExecute());
			newCartset.setGroupRead(params_.getGroupRead());
			newCartset.setGroupWrite(params_.getGroupWrite());
			newCartset.setName(params_.getName());
			newCartset.setOwnerGroup(group);
			newCartset.setOwner(owner);
			newCartset.setParent(parent);
			newCartset.setUserExecute(params_.getUserExecute());
			newCartset.setUserRead(params_.getUserRead());
			newCartset.setUserWrite(params_.getUserWrite());
			session.save(newCartset);
			
			PermissionedCartset pc = authoriser.getFileAuthorisation(newCartset, new PermissionedCartset());
			if(pc.isRead()) {
				response.setPermissionedCartset(pc);
				//This ensures that we don't have any stale collections 
				pc.getItem().makeSafe();
			}
		} catch (Exception e) {
			ts.setRollbackOnly();
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return response;
	}
	
	//TODO: For some reason this doesn't return the page number?!
	@Override
	public AddCartwallResponse addCartwall(AddCartwallRequest params_) {
		AddCartwallResponse response = new AddCartwallResponse(params_);
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Cartset cartset = getCartset(session, params_.getCartsetID());
			if(cartset == null) {
				//TODO Throw error
			}
			Cartwall newCartwall = new Cartwall();
			newCartwall.setName(params_.getName());
			newCartwall.setDescription(params_.getDescription());
			cartset.addCartwall(newCartwall);
			session.update(cartset);
			response.setCartwall(newCartwall);
		} catch (Exception e) {
			ts.setRollbackOnly();
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return response;
	}

	public void afterPropertiesSet() throws Exception {
		
	}
	
	protected Cartset getCartset(Session session, Long cartsetID) {
		Query query = session.createQuery("from Cartset where fileID=?");
		query.setLong(0, cartsetID);
		return (Cartset) query.uniqueResult();
	}

}
