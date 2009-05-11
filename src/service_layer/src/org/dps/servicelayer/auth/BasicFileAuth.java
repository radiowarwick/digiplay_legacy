package org.dps.servicelayer.auth;

import org.dps.servicelayer.common.PermissionedItem;
import org.dps.servicelayer.dto.File;

/**
 * A basic auth class that assumes everyone has access to everything.
 * @author Phil
 *
 */
public class BasicFileAuth implements IFileAuthoriser {

	public <T extends File, U extends PermissionedItem<T>> U getFileAuthorisation(
			T item_, U holder_) {
		holder_.setItem(item_);
		holder_.setRead(true);
		holder_.setWrite(true);
		holder_.setExecute(true);
		return holder_;
	}

//	public <T extends File, U extends PermissionedItem<V>, V extends SummaryItem<T>> U getFileSummaryAuthorisation(
//			T item_, U holder_, V summary_) {
//		summary_.build(item_);
//		holder_.setItem(summary_);
//		holder_.setRead(true);
//		holder_.setWrite(true);
//		holder_.setExecute(true);
//		return holder_;
//	}

}
